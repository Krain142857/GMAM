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
IfExpr::IfExpr(Expr *cond, Expr *true_b, Expr *false_b, Location *l) {
    setBasicInfo(IFEXPR, l);
    condition = cond;
    true_brch = true_b;
    false_brch = false_b;
}

/* Visits the current node.
 *
 * PARAMETERS:
 *   v       - the visitor
 */
void IfExpr::accept(Visitor *v) { v->visit(this); }

/* Prints the current AST node.
 *
 * PARAMETERS:
 *   os      - the output stream
 */
void IfExpr::dumpTo(std::ostream &os) {
    ASTNode::dumpTo(os);
    os << condition << "?" << true_brch << ":" << false_brch << ")";
}
