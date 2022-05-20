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
MacroExpr::MacroExpr(std::string nm, ArguList *argu, Location *l) {

    setBasicInfo(MACROEXPR, l);
    name = nm;
    arguments = argu;
}

/* Visits the current node.
 *
 * PARAMETERS:
 *   v       - the visitor
 */
void MacroExpr::accept(Visitor *v) { v->visit(this); }

/* Prints the current AST node.
 *
 * PARAMETERS:
 *   os      - the output stream
 */
void MacroExpr::dumpTo(std::ostream &os) {
    ASTNode::dumpTo(os);
    os << " " << name << " " << arguments << ")";
}
