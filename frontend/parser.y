/*****************************************************
 *
 *  Krain
 */
%output "parser.cpp"
%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%define api.token.constructor
%define parse.assert


%locations
/* SECTION I: preamble inclusion */

%code requires{
#include "ast/ast.hpp"
#include "define.hpp"
#include "location.hpp"
#include "parser.hpp"
#include <iostream>
using namespace GMAM;

void yyerror (char const *);
//void setParseTree(ast::Program* tree);

/* This macro is provided for your convenience. */
#define POS(pos)    (new Location(pos.begin.line, pos.begin.column))


void scan_begin(const char* filename);
void scan_end();
void setParseTree(ast::Program* tree);
}
%code{
  #include "compiler.hpp"
}
/* SECTION II: definition & declaration */

/*   SUBSECTION 2.1: token(terminal) declaration */
%define api.token.prefix {TOK_}


%token
   END  0  "end of file"
   LBRACE "{"
   RBRACE "}"
   LBRACK "["
   RBRACK "]"
   SEMICOLON ";"
;
%token <std::string> IDENTIFIER "identifier"
%token <std::string> RAWSTRING "rawstring"
%token <int> ICONST "iconst"

%nterm<GMAM::ast::Step *> Step
%nterm<GMAM::ast::RawString *> String
%nterm<GMAM::ast::ASTList *> DeclOrStep 
%nterm<GMAM::ast::StringList *> MacroOrString

/*   SUBSECTION 2.2: associativeness & precedences */
%nonassoc LBRACE

%{
  /* we have to include scanner.hpp here... */
#define YY_NO_UNISTD_H 1
%}

/*   SUBSECTION 2.5: start symbol of the grammar */
%start Program

/* SECTION III: grammar rules (and actions) */
%%
Program     : DeclOrStep 
                { setParseTree(new ast::Program($1, POS(@1))); }
            ;

DeclOrStep  : /* empty */
                { $$ = new ast::ASTList(); }
            | DeclOrStep Step
                { $1->push_back($2);
                  $$ = $1; }
            ;

Step        : LBRACE MacroOrString RBRACE LBRACK ICONST RBRACK SEMICOLON
                { $$ = new ast::Step($2, $5, POS(@1)); }
            | LBRACK ICONST RBRACK LBRACE MacroOrString RBRACE SEMICOLON
                { $$ = new ast::Step($5, $2, POS(@1)); }
            ;

MacroOrString   : /* empty */
                    { $$ = new ast::StringList(); }
                | MacroOrString String
                    { $1->push_back($2);
                      $$ = $1; }
                ;

String      : RAWSTRING
                { $$ = new ast::RawString($1, POS(@1)); }
            ;

%%

/* SECTION IV: customized section */
#include "compiler.hpp"
#include <cstdio>
using namespace GMAM;

extern int myline, mycol;   // defined in scanner.l
static ast::Program* ptree = NULL;

// bison will generate code to invoke me
void yyerror (char const *msg) {
    std::cerr << "yyerror: " << msg << std::endl;
    //err::issue(new Location(myline, mycol), new err::SyntaxError(msg));
    scan_end();
    std::exit(1);
}


// call me when the Program symbol is reduced
void setParseTree(ast::Program* tree) {
    ptree = tree;
}

/* Parses a given mind source file.
 *
 * PARAMETERS:
 *   filename - name of the source file
 * RETURNS:
 *   the parse tree (in the form of abstract syntax tree)
 * NOTE:
 *   should any syntax error occur, this function would not return.
 */
ast::Program* GMAM::GMAMCompiler::parseFile(const char* filename) {  
    scan_begin(filename);
    /* if (NULL == filename)
        yyin = stdin;
    else
        yyin = std::fopen(filename, "r"); */
    yy::parser parse;
    parse();
    scan_end();
    /* if (yyin != stdin)
        std::fclose(yyin); */
    return ptree;
}

void yy::parser::error (const location_type& l, const std::string& m)
{
    std::cerr << l << ": " << m << '\n';
    //err::issue(new Location(l.begin.line, l.begin.column), new err::SyntaxError(m));
    
    scan_end();
    std::exit(1);
}
