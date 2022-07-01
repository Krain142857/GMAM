#ifndef __GMAM_DEFINE__
#define __GMAM_DEFINE__

#include <iostream>
#include <list>

// the prefix of an ast attribution
#define ATTR(x) _attr_##x##_

namespace GMAM {

    #ifndef GMAM_LOCATION_DEFINED
    struct Location;
    #endif
    
    #ifndef GMAM_AST_DEFINED
    namespace ast {
        class Visitor;

        class ASTNode;
        class Program;
        class Argument;
        class VarDef;
        class MacroDef;
        class Step;
        class InitArgu;
        class Expr;
        class CompExpr;
        class Interval;
        class SingleInt;
        class RawString;
        class VarExpr;
        class MacroExpr;
        class IfExpr;
        class EquExpr;

        // the lists are not ASTNode
        typedef std::list<ASTNode *> ASTList;        // list of Function
        typedef std::list<Expr *> ExprList;
        typedef std::list<VarDef *> VarList;
        typedef std::list<Argument *> ArguList;

    } // namespace ast

    #endif

    #ifndef GMAM_SCOPE_DEFINED
    namespace scope {
    class Scope;

    class MacroScope;
    class GlobalScope;
    //class LocalScope;
    } // namespace scope
    #endif

    #ifndef GMAM_SCOPESTACK_DEFINED
    namespace scope {
    class ScopeStack;
    }
    #endif

    #ifndef GMAM_SYMB_DEFINED
    namespace symb {
    class Symbol;

    class Macro;
    class Variable;
    } // namespace symb
    #endif

    #ifndef GMAM_STEP_DEFINED
    namespace builder{
        struct Step;
    }
    #endif

    #ifndef GMAM_TIMELINE_DEFINED
    namespace builder{
        class Timeline;
    }
    #endif

    #ifndef GMAM_TRANSLATION_DEFINED
    class Translation;
    #endif  

    #ifndef GMAM_BUILD_SYMBOL_DEFINED
    class BuildSymbol;
    #endif  
    
    typedef enum {
        NULL_E,
        INTERVAL_E,
        INT_E,
        STRING_E,
        ERROR_E,
        DEFAULT_E,
    } ExprType;

    struct ComputeValue {
        ComputeValue() {
            type = NULL_E;
            intV = 0;
            strV = "";
            begin = 0;
            diff = 0;
            end = 0;
            include_end = false;
        }
        ExprType type;
        int intV;
        std::string strV;
        int begin;
        int diff;
        int end;
        bool include_end;
    };

    std::ostream &operator<<(std::ostream &os, Location *p);
    std::ostream &operator<<(std::ostream &os, ExprType p);
    std::ostream &operator<<(std::ostream &os, ast::ASTNode *p);
    std::ostream &operator<<(std::ostream &os, ast::ASTList *p);
    std::ostream &operator<<(std::ostream &os, ast::ExprList *p);
    std::ostream &operator<<(std::ostream &os, ast::VarList *p);
    std::ostream &operator<<(std::ostream &os, ast::ArguList *p);
    std::ostream &operator<<(std::ostream &os, symb::Symbol *p);
    std::ostream &operator<<(std::ostream &os, scope::Scope *p);
    
    extern scope::ScopeStack *scopes;

    extern int num_of_errors;
}

#endif