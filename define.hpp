#ifndef __GMAM_DEFINE__
#define __GMAM_DEFINE__

#include <iostream>
#include <list>

namespace GMAM {

    #ifndef MIND_LOCATION_DEFINED
    struct Location;
    #endif
    
    #ifndef GMAM_AST_DEFINED
    namespace ast {
        class Visitor;

        class ASTNode;
        class Program;
        class Step;
        class StringNode;
        class RawString;

        // the lists are not ASTNode
        typedef std::list<ASTNode *> ASTList;        // list of Function
        typedef std::list<StringNode *> StringList;        // list of Function

    } // namespace ast

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
    
    std::ostream &operator<<(std::ostream &os, ast::ASTNode *p);
    std::ostream &operator<<(std::ostream &os, ast::ASTList *p);
}

#endif