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
Interval::Interval(IntExpr *b, IntExpr *d, IntExpr *e, bool i_e, Location *l) {
    setBasicInfo(INTERVAL, l);
    begin = b;
    diff = d;
    end = e;
    include_end = i_e;
    kind_i = INTERVAL_L;
}

/* Visits the current node.
 *
 * PARAMETERS:
 *   v       - the visitor
 */
void Interval::accept(Visitor *v) { v->visit(this); }

/* Prints the current AST node.
 *
 * PARAMETERS:
 *   os      - the output stream
 */
void Interval::dumpTo(std::ostream &os) {
    ASTNode::dumpTo(os);
    os << begin << ":" << diff << ":" << end << " " << include_end << ")";
}
