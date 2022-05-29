/*****************************************************
 *
 *  Krain
 */

#include "translate/translation.hpp"
#include "ast/ast.hpp"
#include "symb/symbol.hpp"
#include "builder/step.hpp"
#include <iostream>
#include <list>

using namespace GMAM;

/* Checks whether an ast::Expr conforms to the expecting type.
 *
 * NOTE:
 *   if the expression type is BaseType::Error, we accept it as a legal case.
 * PARAMETERS:
 *   e     - the ast::Expr node
 *   t     - the expected type
 * SIDE-EFFECTS:
 *   Unexpected Type Error may be issued
 */
static bool expect(ast::Expr *e, ExprType t) {
    bool accepted = false;
    switch (t) {
    case STRING_E:
        switch (e->cv.type) {
        case STRING_E:
        case INT_E:
            accepted = true;
            break;
        
        default:
            break;
        }
        break;
    
    case INTERVAL_E:
        switch (e->cv.type) {
        case INTERVAL_E:
        case INT_E:
            accepted = true;
            break;
        
        default:
            break;
        }
        break;

    case INT_E:
        switch (e->cv.type) {
        case INT_E:
            accepted = true;
            break;
        
        default:
            break;
        }
        break;

    default:
        break;
    }
    if (!accepted && t != ERROR_E) {
        std::cout << "Unexpected Type Error at" << e->getLocation() << " " << e->cv.type << " can not be converted to " << t << std::endl;
    }
    return accepted;
}

Translation::Translation(builder::Timeline *tl) {
    timeline = tl;
    cv_stack = new std::vector<ComputeValue>();
}

void Translation::visit(ast::Program *p) {
    for (auto i : *(p->decl_or_steps)) {
        if (i->getKind() != ast::ASTNode::MACRODEF)
            i->accept(this);
    }
}

void Translation::visit(ast::VarDef *p) {
    if (p->value != NULL) p->value->accept(this);
    symb::Variable *v = p->ATTR(sym);
    v->cv = p->value->cv;
}

void Translation::visit(ast::MacroDef *p) {
    int n = p->parameters->size();
    int sp = cv_stack->size() - n;
    int i = 0;
    for (auto j : *(p->parameters)) {
        if ((*cv_stack)[sp + i].type == DEFAULT_E) {
            j->accept(this);
        } else {
            j->ATTR(sym)->cv = (*cv_stack)[sp + i];
        }
        i++;
    }
    p->value->accept(this);
}

void Translation::visit(ast::Step *p) {
    p->macro_or_strings->accept(this);
    for (auto i : *(p->step_pos)) {
        i->accept(this);
        if (i->cv.type == INTERVAL_E) {
            if (i->cv.include_end) {
                for (int k = i->cv.begin; k <= i->cv.end; k += i->cv.diff) {
                    builder::Step *step = timeline->getStepPtr(k);
                    step->content.append(p->macro_or_strings->cv.strV);
                }
            } else {
                for (int k = i->cv.begin; k < i->cv.end; k += i->cv.diff) {
                    builder::Step *step = timeline->getStepPtr(k);
                    step->content.append(p->macro_or_strings->cv.strV);
                }
            }
        } else if (i->cv.type == INT_E) {
            builder::Step *step = timeline->getStepPtr(i->cv.intV);
            step->content.append(p->macro_or_strings->cv.strV);
        }
    }

}

void Translation::visit(ast::InitArgu *p) {
    p->value->accept(this);
    p->cv = p->value->cv;
}

void Translation::visit(ast::CompExpr *p) {
    p->cv.type = STRING_E;
    p->cv.strV = "";
    for (auto j : *(p->exprs)) {
        j->accept(this);
        if (expect(j, STRING_E)) {
            if (j->cv.type == INT_E)
                p->cv.strV.append(std::to_string(j->cv.intV));
            else 
                p->cv.strV.append(j->cv.strV);
        }
    }
}

void Translation::visit(ast::Interval *p) {
    p->begin->accept(this);
    if (!expect(p->begin, INT_E)) goto issue_error_type;
    p->diff->accept(this);
    if (!expect(p->diff, INT_E)) goto issue_error_type;
    p->end->accept(this);
    if (!expect(p->end, INT_E)) goto issue_error_type;
    
    p->cv.type = INTERVAL_E;
    p->cv.begin = p->begin->cv.intV;
    p->cv.diff = p->diff->cv.intV;
    p->cv.end = p->end->cv.intV;
    p->cv.include_end = p->include_end;
    return;

issue_error_type:
    p->cv.type = INTERVAL_E;
}

void Translation::visit(ast::SingleInt *p) {
    p->cv.type = INT_E;
    p->cv.intV = p->value;
}

void Translation::visit(ast::RawString *p) {
    p->cv.type = STRING_E;
    p->cv.strV = p->raw_s;
}

void Translation::visit(ast::VarExpr *p) {
    symb::Variable *v = p->ATTR(sym);
    p->cv = v->cv;
}

void Translation::visit(ast::MacroExpr *p) {
    symb::Macro *m = p->ATTR(sym);
    
    int n = m->numOfParameters();
    int sp = cv_stack->size();
    ComputeValue t;
    t.type = DEFAULT_E;
    for (int i = 0; i < n; i++) {
        cv_stack->push_back(t);
    }

    

    m->alloc_begin();
    int pos = 0;
    Location *loc = NULL;
    for (auto j : *(p->arguments)) {
        j->accept(this);
        if (j->getKind() == ast::ASTNode::INITARGU) {
            ast::InitArgu *v = dynamic_cast<ast::InitArgu *>(j);
            pos = m->alloc_find(v->name);
            if (pos < 0) {
                loc = j->getLocation();
                goto issue_error_type;
            }
            (*cv_stack)[sp + pos] = j->cv;
        } else {
            pos = m->alloc_first();
            if (pos < 0) {
                loc = j->getLocation();
                goto issue_error_type;
            }
            (*cv_stack)[sp + pos] = j->cv;
        }
    }

    
    if (!m->alloc_finish()) {
        loc = p->getLocation();
        goto issue_error_type;
    }

    

    m->getOwner()->accept(this);
    p->cv = m->getOwner()->value->cv;

    for (int i = 0; i < n; i++) cv_stack->pop_back();
    return;

issue_error_type:
    switch (pos) {
    case symb::NOT_FOUND :
        std::cout << "Not Found Argument Name at " << loc << std::endl; 
        break;
    case symb::NO_SPACE :
        std::cout << "Too Many Argument Name at " << loc << std::endl; 
        break;
    case symb::MULTI_ALLO :
        std::cout << "Duplicate Argument Name at " << loc << std::endl; 
        break;
    
    default:
        break;
    }
    for (int i = 0; i < n; i++) cv_stack->pop_back();
}

