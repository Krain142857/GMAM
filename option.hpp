/*****************************************************
 *  Definition of Command Line Options.
 *
 *  If you'd like to see the option description, please
 *  look for "showUsage()" function in options.cpp.
 *
 *  Keltin Leung 
 */

#ifndef __GMAM_OPTIONS__
#define __GMAM_OPTIONS__

#include <vector>

namespace GMAM {

/* Command line options.
 */
class Option {
public:
    static std::vector<const char *> *getInput(void);
    static const char *getOutput(void);
    static void parse(int argc, char **argv); // Parses the command line

private:
    static std::vector<const char *> *input;  // Input file names
    static const char *output; // Output file name

    Option() { /* do not instantiate me */
    }
};

} // namespace GMAM

#endif // __GMAM_OPTIONS__
