/*****************************************************
 *
 *  Krain
 */

#include "ast/ast.hpp"
#include "visitor.hpp"
#include "define.hpp"

using namespace GMAM;
using namespace GMAM::ast;

/* Creates a new Program node.
 *
 * PARAMETERS:
 *   flist   - list of the contained function definitions
 *   l       - position in the source text
 */
MacroDef::MacroDef(std::string nm, VarList *para, Expr *v, Location *l) {

    setBasicInfo(MACRODEF, l);
    name = nm;
    parameters = para;
    value = v;
}

/* Visits the current node.
 *
 * PARAMETERS:
 *   v       - the visitor
 */
void MacroDef::accept(Visitor *v) { v->visit(this); }

/* Prints the current AST node.
 *
 * PARAMETERS:
 *   os      - the output stream
 */
void MacroDef::dumpTo(std::ostream &os) {
    ASTNode::dumpTo(os);
    os << " " << name << " " << parameters << " " << value << ")";
}
