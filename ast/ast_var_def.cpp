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
VarDef::VarDef(std::string nm, Expr *v, Location *l) {

    setBasicInfo(VARDEF, l);
    name = nm;
    value = v;
}

/* Visits the current node.
 *
 * PARAMETERS:
 *   v       - the visitor
 */
void VarDef::accept(Visitor *v) { v->visit(this); }

/* Prints the current AST node.
 *
 * PARAMETERS:
 *   os      - the output stream
 */
void VarDef::dumpTo(std::ostream &os) {
    ASTNode::dumpTo(os);
    os << " " << name << " " << value << ")";
}
