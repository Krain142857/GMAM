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
VarExpr::VarExpr(std::string nm, Location *l) {

    setBasicInfo(VAREXPR, l);
    name = nm;
}

/* Visits the current node.
 *
 * PARAMETERS:
 *   v       - the visitor
 */
void VarExpr::accept(Visitor *v) { v->visit(this); }

/* Prints the current AST node.
 *
 * PARAMETERS:
 *   os      - the output stream
 */
void VarExpr::dumpTo(std::ostream &os) {
    ASTNode::dumpTo(os);
    os << " " << name << ")";
}
