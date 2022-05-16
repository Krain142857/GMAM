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
                INTERVAL,
                SINGLEINT,
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
            void extend(Program *);
        };

        class Step : public ASTNode {
        public:
            Step(StringList *m_or_s, IntList *pos, Location *l);

            virtual void accept(Visitor *);
            virtual void dumpTo(std::ostream &);

        public:
            StringList *macro_or_strings;
            IntList *step_pos;
        };

        /* NOTE:
         *   it is purely an interface.
         */
        class ListableInt : public ASTNode {
        public:
            typedef enum {
                INTERVAL_L,
                INTEXPR_L,
            } ListIntType;
        public:
            ListIntType kind_i;
        };

        class Interval : public ListableInt {
        public:
            Interval(IntExpr *b, IntExpr *d, IntExpr *e, bool i_e, Location *l);

            virtual void accept(Visitor *);
            virtual void dumpTo(std::ostream &);
        public:
            IntExpr *begin, *diff, *end;
            bool include_end;
        };

        /* NOTE:
         *   it is purely an interface.
         */
        class IntExpr : public ListableInt {
        public:
            IntExpr() {kind_i = INTEXPR_L;}
        public:
            int ATTR(val);
        };


        class SingleInt : public IntExpr {
        public:
            SingleInt(int v, Location *l);

            virtual void accept(Visitor *);
            virtual void dumpTo(std::ostream &);        
        public:  
            int value;
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