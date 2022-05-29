#include "compiler.hpp"
#include "builder/timeline.hpp"
#include "translate/translation.hpp"
#include "translate/build_symbol.hpp"
#include "ast/ast.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
using namespace GMAM;

GMAMCompiler::GMAMCompiler() {
    program = NULL;
    timeline = new builder::Timeline();
}

void GMAMCompiler::parse(const char *inputFile) {
    if (program == NULL) program = parseFile(inputFile);
    else {
        ast::Program *newTree = parseFile(inputFile);
        program->extend(newTree);
    }
}

void GMAMCompiler::type_check() {
    program->accept(new BuildSymbol());
}

void GMAMCompiler::compile() {
    program->accept(new Translation(timeline));
}

void GMAMCompiler::debug_parse(std::ostream &os) {
    os << program << std::endl;
}

void GMAMCompiler::debug_type_check(std::ostream &os) {
    os << (scope::Scope *)program->ATTR(gscope) << std::endl;
}

void GMAMCompiler::debug_compile(std::ostream &os) {
    timeline->debug_print(os);
}

void GMAMCompiler::final_print(std::ostream &os) {
    timeline->final_print(os);
}