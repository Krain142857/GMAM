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
    DEF  "def"
    LBRACE "{"
    RBRACE "}"
    LBRACK "["
    RBRACK "]"
    SEMICOLON ";"
    COMMA ","
    COLON ":"
    INCLUDEEND "++"
    ASSIGN "="
    EQU "=="
    QUESTION "?"
    LPAREN "("
    RPAREN ")"
    AT "@"
;
%token <std::string> IDENTIFIER "identifier"
%token <std::string> RAWSTRING "rawstring"
%token <int> ICONST "iconst"

%nterm<GMAM::ast::ASTList *> DeclOrStep 
%nterm<GMAM::ast::VarDef *> VarDef SingleIdtf IdtfInit
%nterm<GMAM::ast::MacroDef *> MacroDef
%nterm<GMAM::ast::Step *> Step
%nterm<GMAM::ast::Expr *> Expr Expr_1
%nterm<GMAM::ast::ExprList *> ExprList
%nterm<GMAM::ast::VarList *> VarList
%nterm<GMAM::ast::ArguList *> ArguList

/*   SUBSECTION 2.2: associativeness & precedences */
%right QUESTION COLON
%left EQU

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
            | DeclOrStep VarDef
                { $1->push_back($2);
                  $$ = $1; }
            | DeclOrStep MacroDef
                { $1->push_back($2);
                  $$ = $1; }
            ;


SingleIdtf  : IDENTIFIER
                { $$ = new ast::VarDef($1, NULL, POS(@1)); }
            ;

IdtfInit    : IDENTIFIER ASSIGN Expr
                { $$ = new ast::VarDef($1, $3, POS(@1)); }
            ;

VarDef      : DEF IdtfInit
                { $$ = $2; }
            ;

MacroDef    : DEF IDENTIFIER AT LPAREN VarList RPAREN ASSIGN Expr
                { $$ = new ast::MacroDef($2, $5, $8, POS(@1)); }
            ;

Step        : LBRACE ExprList RBRACE LBRACK ExprList RBRACK SEMICOLON
                { $$ = new ast::Step(new ast::CompExpr($2, POS(@1)), $5, POS(@1)); }
            | LBRACK ExprList RBRACK LBRACE ExprList RBRACE SEMICOLON
                { $$ = new ast::Step(new ast::CompExpr($5, POS(@1)), $2, POS(@1)); }
            ;

Expr        : Expr COLON Expr_1 COLON Expr_1
                { $$ = new ast::Interval($1, $3, $5, false, POS(@1)); }
            | Expr COLON Expr_1 COLON Expr_1 INCLUDEEND
                { $$ = new ast::Interval($1, $3, $5, true, POS(@1)); }
            | Expr_1
                { $$ = $1; }
            ;

Expr_1      : RAWSTRING
                { $$ = new ast::RawString($1, POS(@1)); }
            | ICONST 
                { $$ = new ast::SingleInt($1, POS(@1)); }
            | LBRACE ExprList RBRACE
                { $$ = new ast::CompExpr($2, POS(@1)); }
            | IDENTIFIER 
                { $$ = new ast::VarExpr($1, POS(@1)); }
            | IDENTIFIER AT LPAREN ArguList RPAREN
                { $$ = new ast::MacroExpr($1, $4, POS(@1)); }
            | Expr_1 EQU Expr_1 
                { $$ = new ast::EquExpr($1, $3, POS(@1)); }
            | Expr_1 QUESTION Expr_1 COLON Expr_1
                { $$ = new ast::IfExpr($1, $3, $5, POS(@1)); }
            | LPAREN Expr RPAREN
                { $$ = $2; }
            ;

ExprList    : /* empty */
                { $$ = new ast::ExprList(); }
            | ExprList COMMA
                { $$ = $1; }
            | ExprList Expr
                { $1->push_back($2);
                  $$ = $1; }
            ;

VarList     : /* empty */
                { $$ = new ast::VarList(); }
            | VarList COMMA
                { $$ = $1; }
            | VarList IdtfInit
                { $1->push_back($2);
                  $$ = $1; }   
            | VarList SingleIdtf
                { $1->push_back($2);
                  $$ = $1; }
            ;

ArguList    : /* empty */
                { $$ = new ast::ArguList(); }
            | ArguList COMMA
                { $$ = $1; }
            | ArguList Expr
                { $1->push_back($2);
                  $$ = $1; }
            | ArguList IDENTIFIER ASSIGN Expr
                { $1->push_back(new ast::InitArgu($2, $4, POS(@2)));
                  $$ = $1; }   
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
