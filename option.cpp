#include "option.hpp"
#include <iostream>
#include <cstring>
using namespace GMAM;

std::vector<const char *> *Option::input = new std::vector<const char*>;  // Input file names

const char *Option::output = NULL; // Output file name

static void showUsage(void) {
    std::cout
        << std::endl
        << "Usage: GMAM.exe [-o OUTPUT] SOURCE"
        << std::endl
        << "Options:" << std::endl
        << "  -o  Specifying the name of the output file (DEFAULT: ./output/(SOURCE).timeline.gmx)."
        << std::endl
        << "" << std::endl;
}


/* Gets the input file names.
 *
 * RETURNS:
 *   the input file names
 */
std::vector<const char *> *Option::getInput(void) { return input; }

/* Gets the output file name.
 *
 * RETURNS:
 *   the output file name
 */
const char *Option::getOutput(void) { return output; }

/* Parses the command line.
 *
 * RETURNS:
 *   parse the command line options
 */
void Option::parse(int argc, char **argv) {
    int i = 1;

    while (i < argc) {
        if (strcmp(argv[i], "-o") == 0) {
            if (i >= argc)
                goto bad_option;
            else if (output != NULL)
                goto dup_option;

            ++i;
            output = argv[i];
        } else {
            input->push_back(argv[i]);
        }
        i++;
    }

    if (input->empty())
        goto empty_option;
    // resolve the default values
    return;

dup_option:
    std::cout << "Duplicated option: " << argv[i] << std::endl;
    exit(1);

bad_option:
    std::cout << "Bad option: " << argv[i] << std::endl;
    showUsage();
    exit(1);

empty_option:
    std::cout << "Empty option: " << std::endl;
    showUsage();
    exit(1);
}