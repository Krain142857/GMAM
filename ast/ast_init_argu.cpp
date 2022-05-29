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
InitArgu::InitArgu(std::string nm, Expr *v, Location *l) {

    setBasicInfo(INITARGU, l);
    name = nm;
    value = v;
}

/* Visits the current node.
 *
 * PARAMETERS:
 *   v       - the visitor
 */
void InitArgu::accept(Visitor *v) { v->visit(this); }

/* Prints the current AST node.
 *
 * PARAMETERS:
 *   os      - the output stream
 */
void InitArgu::dumpTo(std::ostream &os) {
    ASTNode::dumpTo(os);
    os << " " << name << " " << value << ")";
}
