/*****************************************************
 *  Krain
 *  %option yylineno noyywrap nounistd nounput bison-locations never-interactive  noinput batch debug
 
*/

%option yylineno noyywrap nounput noinput batch

%option outfile="scanner.cpp"
/* %option outfile="scanner.cpp" header-file="scanner.hpp" */

/* SECTION I: preamble inclusion. */
%{
#include "parser.hpp"
#include "location.hpp"
#include <cstdlib>
#include <iostream>
#include <climits>
#include <string>
using namespace GMAM;
yy::location loc;
std::string stringbuf;
# define YY_DECL \
  yy::parser::symbol_type yylex ()
// ... and declare it for the parser's sake.
YY_DECL;

%}

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns (yyleng);
%}

%{
  // A number symbol corresponding to the value in S.
  yy::parser::symbol_type
  make_ICONST (const std::string &s, const yy::parser::location_type& loc);
%}

/* SECTION II: macro definition */
NEWLINE       (\r|\n|\r\n)
WHITESPACE    ([ \t]+)
INTEGER       ([0-9]+)
IDENTIFIER    ([A-Za-z][_0-9A-Za-z]*)

/* SECTION III: matching rules (and actions) */
%x B C D
%%
{WHITESPACE}  {       }
{NEWLINE}     { loc.lines (yyleng); loc.step (); }

"//"          { BEGIN(C);         }
<C>{NEWLINE}  { BEGIN(0); loc.lines (yyleng); loc.step ();        }
<C><EOF>      { return yy::parser::make_END (loc); }
<C>.          { /* ignore */      }

"/*"          { BEGIN(B); }
<B>"*/"       { BEGIN(0); }
<B>.|\n ;  
<B><EOF> { return yy::parser::make_END (loc); }

"`"          { BEGIN(D); stringbuf.clear(); }
<D>"`"       { BEGIN(0);  
                return yy::parser::make_RAWSTRING(stringbuf, loc);
             } 

<D>[^`]|\n    { stringbuf.push_back(yytext[0]); }
<D>"``"       { stringbuf.push_back('`'); }
<D><EOF>      { throw yy::parser::syntax_error (loc, "lack of end `"); }

"{"          { return yy::parser::make_LBRACE(loc); }
"}"          { return yy::parser::make_RBRACE(loc); }
"["          { return yy::parser::make_LBRACK(loc); }
"]"          { return yy::parser::make_RBRACK(loc); }
";"          { return yy::parser::make_SEMICOLON(loc); }
","          { return yy::parser::make_COMMA(loc); }
":"          { return yy::parser::make_COLON(loc); }
"-"          { return yy::parser::make_MINUS(loc); }

{INTEGER}     {return make_ICONST(yytext, loc);}

<<EOF>> { return yy::parser::make_END (loc); }

%%

/* SECTION IV: customized section */
int myline, mycol;
yy::parser::symbol_type make_ICONST (const std::string &s, const yy::parser::location_type& loc)
{
    errno = 0;
    long n = strtol (s.c_str(), NULL, 10);
    if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
        throw yy::parser::syntax_error (loc, "integer is out of range: " + s);
    return yy::parser::make_ICONST ((int) n, loc);
}

void scan_begin(const char* filename){
    if (NULL == filename)
        yyin = stdin;
    else
        yyin = std::fopen(filename, "r");
}

void scan_end(){
    if (yyin != stdin)
        std::fclose(yyin);
}