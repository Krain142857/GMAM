#ifndef __GMAM_AST__
#define __GMAM_AST__

#include "define.hpp"

#include <string>

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
                VARDEF,
                MACRODEF,
                STEP,
                INITARGU,
                COMPEXPR,
                INTERVAL,
                SINGLEINT,
                RAWSTRING,
                VAREXPR,
                MACROEXPR,
                IFEXPR,
                EQUEXPR,
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
        
        public:
            scope::GlobalScope *ATTR(gscope); // for semantic analysis
        };

        /* NOTE:
         *   it is purely an interface.
         */
        class Argument: public ASTNode {
        public:
            ComputeValue cv;
        };


        class VarDef : public ASTNode {
        public:
            VarDef(std::string nm, Expr *v, Location *l);

            virtual void accept(Visitor *);
            virtual void dumpTo(std::ostream &);

        public:
            std::string name;
            Expr *value;
        
        public:
            symb::Variable *ATTR(sym); // for semantic analysis
        };

        class MacroDef : public ASTNode {
        public:
            MacroDef(std::string nm, VarList *para, Expr *v, Location *l);

            virtual void accept(Visitor *);
            virtual void dumpTo(std::ostream &);

        public:
            std::string name;
            VarList *parameters;
            Expr *value;
        
        public:
            symb::Macro *ATTR(sym); // for semantic analysis
        };

        class Step : public ASTNode {
        public:
            Step(CompExpr *m_or_s, ExprList *pos, Location *l);

            virtual void accept(Visitor *);
            virtual void dumpTo(std::ostream &);

        public:
            CompExpr *macro_or_strings;
            ExprList *step_pos;
        };

        class InitArgu : public Argument {
        public:
            InitArgu(std::string nm, Expr *v, Location *l);

            virtual void accept(Visitor *);
            virtual void dumpTo(std::ostream &);

        public:
            std::string name;
            Expr *value;
        };

        /* NOTE:
         *   it is purely an interface.
         */
        class Expr : public Argument {
        public:
            
        };

        class CompExpr : public Expr {
        public:
            CompExpr(ExprList *es, Location *l);

            virtual void accept(Visitor *);
            virtual void dumpTo(std::ostream &);
        public:
            ExprList *exprs;
        };

        class Interval : public Expr {
        public:
            Interval(Expr *b, Expr *d, Expr *e, bool i_e, Location *l);

            virtual void accept(Visitor *);
            virtual void dumpTo(std::ostream &);
        public:
            Expr *begin, *diff, *end;
            bool include_end;
        };


        class SingleInt : public Expr {
        public:
            SingleInt(int v, Location *l);

            virtual void accept(Visitor *);
            virtual void dumpTo(std::ostream &);        
        public:  
            int value;
        };


        class RawString : public Expr {
        public:
            RawString(std::string s, Location *l);

            virtual void accept(Visitor *);
            virtual void dumpTo(std::ostream &);

        public:
            std::string raw_s;
        };

        class VarExpr : public Expr {
        public:
            VarExpr(std::string nm, Location *l);

            virtual void accept(Visitor *);
            virtual void dumpTo(std::ostream &);

        public:
            std::string name;
        
        public:
            symb::Variable *ATTR(sym); // for semantic analysis
        };
        
        class MacroExpr : public Expr {
        public:
            MacroExpr(std::string nm, ArguList *argu, Location *l);

            virtual void accept(Visitor *);
            virtual void dumpTo(std::ostream &);

        public:
            std::string name;
            ArguList *arguments;
        
        public:
            symb::Macro *ATTR(sym); // for semantic analysis
            std::list<int> *orders;
        };

        class IfExpr : public Expr {
        public:
            IfExpr(Expr *cond, Expr *true_b, Expr *false_b, Location *l);

            virtual void accept(Visitor *);
            virtual void dumpTo(std::ostream &);

        public:
            Expr *condition;
            Expr *true_brch;
            Expr *false_brch;
        };

        class EquExpr : public Expr {
        public:
            EquExpr(Expr *op1, Expr *op2, Location *l);

            virtual void accept(Visitor *);
            virtual void dumpTo(std::ostream &);

        public:
            Expr *e1;
            Expr *e2;
        };
    };
}

#endif