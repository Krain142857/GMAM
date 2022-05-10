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
Step::Step(StringList *m_or_s, int pos, Location *l) {

    setBasicInfo(STEP, l);
    macro_or_strings = m_or_s;
    step_pos = pos;
    ATTR(val) = nullptr;
}

/* Visits the current node.
 *
 * PARAMETERS:
 *   v       - the visitor
 */
void Step::accept(Visitor *v) { v->visit(this); }

/* Prints the current AST node.
 *
 * PARAMETERS:
 *   os      - the output stream
 */
void Step::dumpTo(std::ostream &os) {
    ASTNode::dumpTo(os);
    os << " " << step_pos << " " << macro_or_strings << ")";
}
