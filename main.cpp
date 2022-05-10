#include "compiler.hpp"
#include "utils.hpp"
using namespace GMAM;

int main(int argc, char **argv) {
    GMAMCompiler *c = new GMAMCompiler();
    if (argc >= 1) {
        if (!check_filename(argv[1])) {
            std::cout << "Error: Filename should end with .tl" << std::endl;
            exit(1);
        }
        c->compile(argc, argv);
    } else {
        std::cout << "Error: No File Arguments" << std::endl;
        exit(1);
    }
}