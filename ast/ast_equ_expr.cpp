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
EquExpr::EquExpr(Expr *op1, Expr *op2, Location *l) {
    setBasicInfo(EQUEXPR, l);
    e1 = op1;
    e2 = op2;
}

/* Visits the current node.
 *
 * PARAMETERS:
 *   v       - the visitor
 */
void EquExpr::accept(Visitor *v) { v->visit(this); }

/* Prints the current AST node.
 *
 * PARAMETERS:
 *   os      - the output stream
 */
void EquExpr::dumpTo(std::ostream &os) {
    ASTNode::dumpTo(os);
    os << e1 << "==" << e2 << ")";
}
