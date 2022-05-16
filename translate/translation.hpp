/*****************************************************
 *  Definition of the two AST translation passes.
 *
 *  Keltin Leung 
 */

#ifndef __GMAM_TRANSLATION__INTERNAL__
#define __GMAM_TRANSLATION__INTERNAL__

#include "visitor.hpp"
#include "builder/timeline.hpp"
#include "define.hpp"
#include <string>

namespace GMAM {

    #define GMAM_TRANSLATION_DEFINED
    class Translation : public ast::Visitor {
    public:
        Translation(builder::Timeline *tl);

        virtual void visit(ast::Program *);
        virtual void visit(ast::Step *);
        virtual void visit(ast::Interval *);
        virtual void visit(ast::SingleInt *);
        virtual void visit(ast::RawString *);

        virtual ~Translation() {}

    private:
        builder::Timeline *timeline;
    };
} // namespace GMAM

#endif // __GMAM_TRANSLATION__INTERNAL__
