#include "scope/scope.hpp"
#include "symb/symbol.hpp"
#include <cassert>

using namespace GMAM;
using namespace GMAM::symb;
using namespace GMAM::scope;

/* Constructor.
 *
 * PARAMETERS:
 *   n     - the variable name
 *   t     - the type
 *   l     - the definition location in the source code
 */
Variable::Variable(std::string n, bool i, Location *l) {

    name = n;
    type = NULL_E;
    loc = l;
    order = -1;

    is_parameter = false;
    init = i;
    mark = 0;
    defined_in = NULL;
}

/* Sets the parameter flag (i.e. it is a parameter).
 *
 */
void Variable::setParameter(void) { is_parameter = true; }

/* Tests whether it is a parameter.
 *
 * RETURNS:
 *   true if it is a parameter; false otherwise
 */
bool Variable::isParameter(void) { return is_parameter; }

bool Variable::isInit(void) { return init; }

/* Tests whether it is a local variable.
 *
 * RETURNS:
 *   true if it is a local variable, false otherwise
 */
bool Variable::isLocalVar(void) {
    assert(NULL != defined_in);

    return (defined_in->isFuncScope() && !is_parameter);
}

/* Tests whether it is a global variable.
 *
 * RETURNS:
 *   true if it is a global variable, false otherwise
 */
bool Variable::isGlobalVar(void) {
    assert(NULL != defined_in);

    return defined_in->isGlobalScope();
}

/* Tests whether this symbol is a Variable.
 *
 * RETURNS:
 *   true
 */
bool Variable::isVariable(void) { return true; }

/* Prints this symbol.
 *
 * PARAMETERS:
 *   os    - the output stream
 */
void Variable::dump(std::ostream &os) {
    os << loc << " -> variable ";
    if (is_parameter)
        os << "@" << (name);
    else
        os << (name);
    os << " : " << type;
}
