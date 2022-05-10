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
Program::Program(ASTList *d_or_s, Location *l) {

    setBasicInfo(PROGRAM, l);
    decl_or_steps = d_or_s;
}

/* Visits the current node.
 *
 * PARAMETERS:
 *   v       - the visitor
 */
void Program::accept(Visitor *v) { v->visit(this); }

/* Prints the current AST node.
 *
 * PARAMETERS:
 *   os      - the output stream
 */
void Program::dumpTo(std::ostream &os) {
    ASTNode::dumpTo(os);
    os << decl_or_steps << ")";
}
