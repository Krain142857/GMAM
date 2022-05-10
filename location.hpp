/*****************************************************
 *  Location Record.
 *
 *
 *  Krain
 */

#ifndef __GMAM_LOCATION__
#define __GMAM_LOCATION__

#include <iostream>

namespace GMAM {

#define GMAM_LOCATION_DEFINED
struct Location {
    int line;
    int col;

    Location(int l, int c) : line(l), col(c) {}

    Location(int l) : line(l), col(-1) {}
};

inline bool operator<(const Location &lhs, const Location &rhs) {
    return lhs.line < rhs.line || (lhs.line == rhs.line && lhs.col < rhs.col);
}

} // namespace GMAM

#endif // __GMAM_LOCATION__
