/*****************************************************
 *  GMAMCompiler class.
 *
 *  Krain
 */

#ifndef __GMAM_COMPILER__
#define __GMAM_COMPILER__

#include "define.hpp"
#include "parser.hpp"
#include "iostream"

#define YY_DECL yy::parser::symbol_type yylex()
// ... and declare it for the parser's sake.
YY_DECL;
namespace GMAM {

class GMAMCompiler {
private:
    ast::Program *program;
    builder::Timeline *timeline;
public:
    GMAMCompiler();
    ast::Program* parseFile(const char *filename);
    void parse(const char *filename);
    void compile();
    void debug_parse(std::ostream &os);
    void debug_compile(std::ostream &os);
    void final_print(std::ostream &os);
};

} // namespace GMAM

#endif // __GMAM_COMPILER__
