#include "compiler.hpp"
#include "define.hpp"
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
    //c->debug_parse(std::cout);
    c->type_check();
    if (num_of_errors > 0) exit(1); 
    //c->debug_type_check(std::cout);
    c->compile();
    const char *outputfile = Option::getOutput();
    std::ofstream output;
    if (outputfile != NULL) output.open(std::string(outputfile), std::ios::out);
    else output.open(standard_output(input->back()), std::ios::out);
    c->debug_compile(std::cout);
    c->final_print(output);
    return 0;
}