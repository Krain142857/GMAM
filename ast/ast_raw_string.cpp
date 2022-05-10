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
RawString::RawString(std::string s, Location *l) {

    setBasicInfo(RAWSTRING, l);
    raw_s = s;
}

/* Visits the current node.
 *
 * PARAMETERS:
 *   v       - the visitor
 */
void RawString::accept(Visitor *v) { v->visit(this); }

/* Prints the current AST node.
 *
 * PARAMETERS:
 *   os      - the output stream
 */
void RawString::dumpTo(std::ostream &os) {
    ASTNode::dumpTo(os);
    os << ")";
}
