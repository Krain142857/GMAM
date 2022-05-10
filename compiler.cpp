#include "compiler.hpp"
#include "builder/timeline.hpp"
#include "translate/translation.hpp"
#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <string>
using namespace GMAM;

void GMAMCompiler::compile(int argc, char **argv) {
    char *inputFile = argv[1];
    ast::Program *tree = parseFile(inputFile);
    builder::Timeline *tl = new builder::Timeline();
    tree->accept(new Translation(tl));
    std::ofstream output;
    if (argc >= 2) output.open(std::string(argv[2]), std::ios::out);
    else output.open(standard_output(inputFile), std::ios::out);
    tl->final_print(output);
}