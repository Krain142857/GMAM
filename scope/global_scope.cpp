#include "scope/scope.hpp"
#include "symb/symbol.hpp"

#include <vector>
#include <algorithm>
#include <cstring>
#include <cassert>

using namespace GMAM;
using namespace GMAM::symb;
using namespace GMAM::scope;

/*  Constructor.
 *
 */
GlobalScope::GlobalScope(void) {
    // just leave it alone
}

/*  Gets the kind of this scope.
 *
 *  RETURNS:
 *    Scope::GLOBAL
 */
Scope::kind_t GlobalScope::getKind(void) { return GLOBAL; }

/*  Declares a symbol in this scope.
 *
 *  PARAMETERS:
 *    s     - the symbol
 */
void GlobalScope::declare(Symbol *s) {
    assert(NULL != s && s->getScope() == NULL);

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
void GlobalScope::dump(std::ostream &os) {
    std::vector<Symbol *> s;
    for (ScopeIterator it = begin(); it != end(); ++it)
        s.push_back(*it);
    std::sort(s.begin(), s.end(), symbol_less());

    os << "GLOBAL SCOPE:";
    for (auto it = s.begin(); it != s.end(); ++it) {
        os << "  " << *it;
    }
}
