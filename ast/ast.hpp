#ifndef __GMAM_AST__
#define __GMAM_AST__

#include "define.hpp"

#include <string>

// the prefix of an ast attribution
#define ATTR(x) ast_attr_##x##_

namespace GMAM {

#define GMAM_AST_DEFINED
    namespace ast {

        /* The base class of all AST nodes.
         *
         * NOTE: Don't instantiate this class.
         *       Please read the description of the subclasses.
         */
        class ASTNode {
        public:
            // types of the AST nodes
            typedef enum {
                PROGRAM,
                STEP,
                RAWSTRING,
            } NodeType;

        protected:
            // names of each kind of the AST nodes
            static const char *node_name[];
            // kind of this node
            NodeType kind;
            // position in the source text
            Location *loc;
            // for subclass constructors only
            virtual void setBasicInfo(NodeType, Location *);

        public:
            // gets the node kind
            virtual NodeType getKind(void);
            // gets the location
            virtual Location *getLocation(void);
            // prints to the specified output stream
            virtual void dumpTo(std::ostream &);
            // for Visitor
            virtual void accept(Visitor *) = 0;
            // remember: let alone the memory deallocation stuff
            virtual ~ASTNode(void) {}
        };


        class Program : public ASTNode {
        public:
            Program(ASTList *d_or_s, Location *l);

            virtual void accept(Visitor *);
            virtual void dumpTo(std::ostream &);

        public:
            ASTList *decl_or_steps;
        };

        class Step : public ASTNode {
        public:
            Step(StringList *m_or_s, int pos, Location *l);

            virtual void accept(Visitor *);
            virtual void dumpTo(std::ostream &);

        public:
            StringList *macro_or_strings;
            int step_pos;
            builder::Step *ATTR(val);
        };

        /* NOTE:
         *   it is purely an interface.
         */
        class StringNode : public ASTNode {
        public:
            typedef enum {
                MACRO,
                RAW,
            } StringType;
        public:
            std::string ATTR(val);
        };

        class RawString : public StringNode {
        public:
            RawString(std::string s, Location *l);

            virtual void accept(Visitor *);
            virtual void dumpTo(std::ostream &);

        public:
            std::string raw_s;
        };
    };
}

#endif