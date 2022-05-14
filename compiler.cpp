#include "compiler.hpp"
#include "builder/timeline.hpp"
#include "translate/translation.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
using namespace GMAM;

GMAMCompiler::GMAMCompiler() {
    program = nullptr;
    timeline = new builder::Timeline();
}

void GMAMCompiler::parse(const char *inputFile) {
    if (program == nullptr) program = parseFile(inputFile);
    else {
        ast::Program *newTree = parseFile(inputFile);
        program->extend(newTree);
    }
}

void GMAMCompiler::compile() {
    program->accept(new Translation(timeline));
}

void GMAMCompiler::final_print(std::ostream &os) {
    timeline->final_print(os);
}