
#ifndef __GMAM_BUILD_SYMBOL__INTERNAL__
#define __GMAM_BUILD_SYMBOL__INTERNAL__

#include "visitor.hpp"
#include "define.hpp"

namespace GMAM {

    #define GMAM_BUILD_SYMBOL_DEFINED
    /* Pass 2 of the semantic analysis.
    */
    class BuildSymbol : public ast::Visitor {
        // Visiting declarations
        virtual void visit(ast::Program *);
        virtual void visit(ast::VarDef *);
        virtual void visit(ast::MacroDef *);
        // Visiting statements
        virtual void visit(ast::Step *);
        // Visiting expressions
        virtual void visit(ast::InitArgu *);
        virtual void visit(ast::CompExpr *);
        virtual void visit(ast::Interval *);
        virtual void visit(ast::VarExpr *);
        virtual void visit(ast::MacroExpr *);
        virtual void visit(ast::IfExpr *);
        virtual void visit(ast::EquExpr *);
    };
} // namespace GMAM

#endif // __GMAM_BUILD_SYMBOL__INTERNAL__
