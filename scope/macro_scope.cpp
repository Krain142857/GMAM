#include "scope/scope.hpp"
#include "symb/symbol.hpp"

#include <vector>
#include <algorithm>
#include <string>
#include <cassert>

using namespace GMAM;
using namespace GMAM::symb;
using namespace GMAM::scope;

/*  Constructor.
 *
 *  PARAMETERS:
 *    o     - the owner of this func    	tion scope
 */
MacroScope::MacroScope(Macro *o) {
    owner = o;
}

/*  Gets the owner of this scope.
 *
 *  RETURNS:
 *    the owner of this function scope
 */
Macro *MacroScope::getOwner(void) { return owner; }

/*  Gets the kind of this scope.
 *
 *  RETURNS:
 *    Scope::FUNCTION
 */
Scope::kind_t MacroScope::getKind(void) { return FUNCTION; }

/*  Declares a symbol in this scope.
 *
 *  PARAMETERS:
 *    s     - the symbol
 */
void MacroScope::declare(Symbol *s) {
    assert(NULL != s && s->isVariable() && s->getScope() == NULL);

    Scope::declare(s);
}

// symbol comparator
struct symbol_less {
    bool operator()(Symbol *s1, Symbol *s2) {
        return (s1->getName().compare(s2->getName()) < 0);
    }
};

/*  Prints the content of this scope.
 *
 *  PARAMETERS:
 *    os    - the output stream
 */
void MacroScope::dump(std::ostream &os) {
    std::vector<Symbol *> s;
    for (ScopeIterator it = begin(); it != end(); ++it)
        s.push_back(*it);
    std::sort(s.begin(), s.end(), symbol_less());

    os << "FUNCTION SCOPE OF '" << (owner->getName()) << "':";
    for (auto it = s.begin(); it != s.end(); ++it) {
        os << "  " << *it;
    }
}
