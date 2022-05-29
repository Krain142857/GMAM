#include "scope/scope.hpp"
#include "symb/symbol.hpp"
#include <cassert>

using namespace GMAM;
using namespace GMAM::symb;
using namespace GMAM::scope;

/* Constructor.
 *
 * NOTE:
 *   the FuncType will be automatically created
 * PARAMETERS:
 *   n       - the function name
 *   resType - the result type
 *   l       - the definition location in the source code
 */
Macro::Macro(std::string n, ast::MacroDef *o, Location *l) {
    name = n;
    loc = l;
    order = -1;
    mark = 0;

    type = NULL_E;
    associated = new MacroScope(this);
    defined_in = NULL;
    parameters = new std::vector<Variable *>();

    allocated = NULL;
    allocatePos = 0;
    owner = o;
}

/* Gets the associated function scope.
 *
 * RETURNS:
 *   the associated function scope
 */
MacroScope *Macro::getAssociatedScope(void) { return associated; }

/* Gets the scope where this symbol is defined.
 *
 * RETURNS:
 *   the scope where this symbol is defined
 */
Scope *Macro::getScope(void) { return defined_in; }

/* Gets the type of this symbol.
 *
 * NOTE:
 *   it is different from the GetResultType()
 * RETURNS:
 *   the corresponding FuncType
 */
ExprType Macro::getType(void) { return type; }

/* Appends a parameter to this function.
 *
 * NOTE:
 *   you should check the correctness of the argument before invoking me
 * PARAMETERS:
 *   arg   - the argument
 */
void Macro::appendParameter(Variable *arg) {//TODO
    if (NULL == arg) return;

    // it is your responsibility to check "arg" before invoking this method
    arg->setParameter();
    arg->setOrder(parameters->size());
    parameters->push_back(arg);
    // usually the symbol has already been added into the associated scope,
    // we just make sure it is right (and we will ignore the duplicated
    // declarations)
    // if (associated->lookup(arg->getName()) == NULL)
    // associated->declare(arg);
}

int Macro::numOfParameters(void) { return parameters->size(); }

/* Tests whether this symbol is a Function.
 *
 * RETURNS:
 *   true
 */
bool Macro::isMacro(void) { return true; }

/* Prints this symbol.
 *
 * PARAMETERS:
 *   os    - the output stream
 */
void Macro::dump(std::ostream &os) {
    os << loc << " -> function " << (name) << " : " << type;
}

ast::MacroDef *Macro::getOwner(void) { return owner; }


void Macro::alloc_begin(void) {
    if (allocated != NULL) delete allocated;
    allocated = new std::vector<bool>(parameters->size(), false);
    allocatePos = 0;
}

void Macro::alloc_update(void) {
    int n = parameters->size();
    while (allocatePos < n && (*allocated)[allocatePos]) allocatePos++;
}

int Macro::alloc_first(void) {
    if (allocatePos >= parameters->size()) return NO_SPACE;
    int value = allocatePos;
    (*allocated)[value] = true;
    alloc_update();
    return value;
}

int Macro::alloc_find(std::string s) {
    if (allocatePos >= parameters->size()) return NO_SPACE;
    int n = parameters->size();
    int i = 0;
    while (i < n) {
        if ((*parameters)[i]->getName() == s) break;
        i++;
    }
    if (i >= n) return NOT_FOUND;
    if ((*allocated)[i]) return MULTI_ALLO;
    (*allocated)[i] = true;
    alloc_update();
    return i;
}

bool Macro::alloc_finish(void) {
    return (allocatePos >= parameters->size() || (*parameters)[allocatePos]->isInit());
}
