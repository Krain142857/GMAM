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
        if (i->getKind() == ast::ASTNode::STEP) {
            ast::Step *s = dynamic_cast<ast::Step *>(i);
            timeline->append(s->ATTR(val));
        }
    }
}

void Translation::visit(ast::Step *p) {
    p->ATTR(val) = new builder::Step();
    p->ATTR(val)->pos = p->step_pos;
    for (auto i : *(p->macro_or_strings)) {
        i->accept(this);
        p->ATTR(val)->content.push_back(i->ATTR(val));
    }
}

void Translation::visit(ast::RawString *p) {
    p->ATTR(val) = p->raw_s;
}