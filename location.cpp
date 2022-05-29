#include <define.hpp>
#include <location.hpp>

/* Prints a location record.
 *
 * PARAMETERS:
 *   os    - the output stream
 *   l     - the location record
 * RETURNS:
 *   the output stream
 */
std::ostream &GMAM::operator<<(std::ostream &os, Location *l) {
    if (NULL == l)
        os << "(UNKNOWN)";
    else if (l->col < 0) {
        os << "(line ";
        os.width(2);
        os << l->line << ")";
    } else {
        os << "(";
        os.width(2);
        os << l->line << ",";
        os.width(2);
        os << l->col << ")";
    }

    return os;
}