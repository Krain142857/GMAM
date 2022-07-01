#include "ast/ast.hpp"
#include "visitor.hpp"
#include "scope/scope_stack.hpp"
#include "scope/scope.hpp"
#include "symb/symbol.hpp"
#include "translate/build_symbol.hpp"

using namespace GMAM;
using namespace GMAM::scope;
using namespace GMAM::symb;

int GMAM::num_of_errors = 0;

/* Visits an ast::Program node.
 *
 * PARAMETERS:
 *   e     - the ast::Program node
 */
void BuildSymbol::visit(ast::Program *p) {
    p->ATTR(gscope) = new GlobalScope();
    scopes->open(p->ATTR(gscope));
    for (auto it : *(p->decl_or_steps))
        it->accept(this);
    scopes->close(); // close the global scope
}

/* Visits an ast::IntConst node.
 *
 * PARAMETERS:
 *   e     - the ast::IntConst node
 */
void BuildSymbol::visit(ast::VarDef *e) {

    if (e->value != NULL) e->value->accept(this);
    
    Symbol *oldV = scopes->lookup(e->name, e->getLocation(), false);
    if (oldV != NULL) {
        std::cout << "Duplicate Define at" << e->getLocation() << " and " << oldV->getDefLocation() << std::endl;
        num_of_errors++;
    }
    else { 
        Variable *v;
        v = new Variable(e->name, e->value != NULL, e->getLocation());
        scopes->declare(v);
        e->ATTR(sym) = v;
    }
}

/* Visits an ast::IntConst node.
 *
 * PARAMETERS:
 *   e     - the ast::IntConst node
 */
void BuildSymbol::visit(ast::MacroDef *e) {

    Symbol *oldM = scopes->lookup(e->name, e->getLocation(), false);
    if (oldM != NULL) {
        std::cout << "Duplicate Define at" << e->getLocation() << " and " << oldM->getDefLocation() << std::endl;
        num_of_errors++;
    }
    else { 
        Macro *m = new Macro(e->name, e, e->getLocation());
        MacroScope *sco = m->getAssociatedScope();
        scopes->open(sco);
        bool init = false; 
        for (auto it : *(e->parameters)) {
            it->accept(this);
            m->appendParameter(it->ATTR(sym));
            if (it->value != NULL) {
                init = true;
            } else {
                if (init) {
                    std::cout << "Init Argument Before Uninit Argument at" << it->getLocation() << std::endl;
                    num_of_errors++;
                    return;
                }
            }
        }
        e->value->accept(this);
        
        scopes->close();
        scopes->declare(m);
        e->ATTR(sym) = m;
    }
}


void BuildSymbol::visit(ast::Step *e) {
    e->macro_or_strings->accept(this);
    for (auto p : *(e->step_pos)) {
        p->accept(this);
    }
}

void BuildSymbol::visit(ast::InitArgu *e) {
    e->value->accept(this);
}

void BuildSymbol::visit(ast::CompExpr *e) {
    for (auto p : *(e->exprs)) {
        p->accept(this);
    }
}

void BuildSymbol::visit(ast::Interval *e) {
    e->begin->accept(this);
    e->diff->accept(this);
    e->end->accept(this);
}

/* Visits an ast::IntConst node.
 *
 * PARAMETERS:
 *   e     - the ast::IntConst node
 */
void BuildSymbol::visit(ast::VarExpr *e) {
    Symbol *v = scopes->lookup(e->name, e->getLocation(), true);
    if (v == NULL) {
        std::cout << "Undefined Identifier at" << e->getLocation() << e->name << std::endl;
        goto issue_error_type;
    }
    else if (v->isMacro()) { 
        std::cout << "Not a Variable at" << e->getLocation() << e->name << std::endl;
        goto issue_error_type;
    } else {
        e->ATTR(sym) = dynamic_cast<Variable *>(v);
    }
    return;

issue_error_type:
    e->ATTR(sym) = NULL;
    num_of_errors++;
}

/* Visits an ast::IntConst node.
 *
 * PARAMETERS:
 *   e     - the ast::IntConst node
 */
void BuildSymbol::visit(ast::MacroExpr *e) {
    Symbol *m = scopes->lookup(e->name, e->getLocation(), false);
    if (m == NULL) {
        std::cout << "Undefined Identifier at " << e->getLocation() << e->name << std::endl;
        goto issue_error_type;
    }
    else if (m->isVariable()) { 
        std::cout << "Not a Macro at " << e->getLocation() << e->name << std::endl;
        goto issue_error_type;
    } else {
        Macro *mac = dynamic_cast<Macro *>(m);
        e->ATTR(sym) = mac;
        for (auto it : *(e->arguments)) {
            it->accept(this);
        }
    }
    return;

issue_error_type:
    e->ATTR(sym) = NULL;
    num_of_errors++;
}

void BuildSymbol::visit(ast::IfExpr *e) {
    e->condition->accept(this);
    e->true_brch->accept(this);
    e->false_brch->accept(this);
}

void BuildSymbol::visit(ast::EquExpr *e) {
    e->e1->accept(this);
    e->e2->accept(this);
}