/*****************************************************
 *
 *  Krain
 */

#include "translate/translation.hpp"
#include "ast/ast.hpp"
#include "builder/step.hpp"
#include <iostream>
#include <list>

using namespace GMAM;

Translation::Translation(builder::Timeline *tl) {
    timeline = tl;
}

void Translation::visit(ast::Program *p) {
    for (auto i : *(p->decl_or_steps)) {
        i->accept(this);
    }
}

void Translation::visit(ast::Step *p) {
    for (auto j : *(p->macro_or_strings)) {
        j->accept(this);
    }
    for (auto i : *(p->step_pos)) {
        i->accept(this);
        if (i->kind_i == ast::ListableInt::INTERVAL_L) {
            ast::Interval *interval = dynamic_cast<ast::Interval *>(i);
            if (interval->include_end) {
                for (int k = interval->begin->ATTR(val); k <= interval->end->ATTR(val); k += interval->diff->ATTR(val)) {
                    builder::Step *step = timeline->getStepPtr(k);
                    for (auto j : *(p->macro_or_strings)) {
                        step->content.push_back(j->ATTR(val));
                    }
                }
            } else {
                for (int k = interval->begin->ATTR(val); k < interval->end->ATTR(val); k += interval->diff->ATTR(val)) {
                    builder::Step *step = timeline->getStepPtr(k);
                    for (auto j : *(p->macro_or_strings)) {
                        step->content.push_back(j->ATTR(val));
                    }
                }
            }
        } else if (i->kind_i == ast::ListableInt::INTEXPR_L) {
            ast::IntExpr *intexpr = dynamic_cast<ast::IntExpr *>(i);
            builder::Step *step = timeline->getStepPtr(intexpr->ATTR(val));
            for (auto j : *(p->macro_or_strings)) {
                step->content.push_back(j->ATTR(val));
            }
        }
    }

}

void Translation::visit(ast::Interval *p) {
    p->begin->accept(this);
    p->diff->accept(this);
    p->end->accept(this);
}

void Translation::visit(ast::SingleInt *p) {
    p->ATTR(val) = p->value;
}

void Translation::visit(ast::RawString *p) {
    p->ATTR(val) = p->raw_s;
}