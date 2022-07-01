
#ifndef __GMAM_TRANSLATION__INTERNAL__
#define __GMAM_TRANSLATION__INTERNAL__

#include "visitor.hpp"
#include "builder/timeline.hpp"
#include "define.hpp"
#include <vector>

namespace GMAM {

    #define GMAM_TRANSLATION_DEFINED
    class Translation : public ast::Visitor {
    public:
        Translation(builder::Timeline *tl);

        virtual void visit(ast::Program *);
        virtual void visit(ast::VarDef *);
        virtual void visit(ast::MacroDef *);
        virtual void visit(ast::Step *);
        virtual void visit(ast::InitArgu *);
        virtual void visit(ast::CompExpr *);
        virtual void visit(ast::Interval *);
        virtual void visit(ast::SingleInt *);
        virtual void visit(ast::RawString *);
        virtual void visit(ast::VarExpr *);
        virtual void visit(ast::MacroExpr *);
        virtual void visit(ast::IfExpr *);
        virtual void visit(ast::EquExpr *);
        
        virtual ~Translation() {}

    private:
        builder::Timeline *timeline;
        std::vector<ComputeValue> *cv_stack;
    };
} // namespace GMAM

#endif // __GMAM_TRANSLATION__INTERNAL__
