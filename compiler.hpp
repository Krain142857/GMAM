/*****************************************************
 *  GMAMCompiler class.
 *
 *  Krain
 */

#ifndef __GMAM_COMPILER__
#define __GMAM_COMPILER__

#include "define.hpp"
#include "parser.hpp"

#define YY_DECL yy::parser::symbol_type yylex()
// ... and declare it for the parser's sake.
YY_DECL;
namespace GMAM {

class GMAMCompiler {
public:
    ast::Program* parseFile(const char* filename);
    void compile(int argc, char **argv);
};

} // namespace GMAM

#endif // __GMAM_COMPILER__
