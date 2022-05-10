/*****************************************************
 *
 *  Krain
 */

#ifndef __GMAM_VISITOR__
#define __GMAM_VISITOR__

#include "ast/ast.hpp"

namespace GMAM {

    namespace ast {
        /*  AST Visitor Pattern.
        *
        *  HOW TO USE:
        *    1. Create a subclass of Visitor;
        *    2. Implement visit(ast::Program*)  (required);
        *    3. Implement the other visiting functions as you need;
        *    4. We provide an empty function body ({  }) instead of
        *       setting it pure (= 0) so that you do not need to
        *       implement all the functions as you do with a pure
        *       interface.
        */
        class Visitor {
        public:
            virtual void visit(Program *) = 0;
            virtual void visit(Step *) {}
            virtual void visit(RawString *) {}

            virtual ~Visitor() {}
        };
    } // namespace ast
} // namespace GMAM

#endif // __GMAM_VISITOR__
