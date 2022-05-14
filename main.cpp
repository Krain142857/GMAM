#include "compiler.hpp"
#include "utils.hpp"
#include "option.hpp"
#include <vector>
#include <fstream>
using namespace GMAM;

int main(int argc, char **argv) {
    GMAMCompiler *c = new GMAMCompiler();
    Option::parse(argc, argv);
    auto input = Option::getInput();
    for (auto filename : *input)
        c->parse(filename);
    c->compile();
    const char *outputfile = Option::getOutput();
    std::ofstream output;
    if (outputfile != nullptr) output.open(std::string(outputfile), std::ios::out);
    else output.open(standard_output((*input)[0]), std::ios::out);
    c->final_print(output);
    return 0;
}