#ifndef __GMAM_SYMBOL__
#define __GMAM_SYMBOL__

#include "define.hpp"

#include <iostream>
#include <string>
#include <vector>

namespace GMAM {

    #define GMAM_SYMB_DEFINED
    namespace symb {
        
        typedef enum {
            NOT_FOUND = -3,
            MULTI_ALLO = -2,
            NO_SPACE = -1,
        } ErrorAllo;

        /* Representation of the data objects in GMAM.
        */
        class Symbol {
        protected:
            // name of this symbol
            std::string name;
            // type of this symbol
            ExprType type;
            // definition location in the source code
            Location *loc;
            // the scope where this symbol is defined
            scope::Scope *defined_in;
            // the order of this symbol
            int order;

        public:
            // auxiliary mark
            int mark;
            // offset of this symbol
            int offset;

            ComputeValue cv;

            // Gets the name of this symbol
            virtual std::string getName(void);
            // Gets the type of this symbol
            virtual ExprType getType(void);
            // Gets the definition location
            virtual Location *getDefLocation(void);
            // Gets the order
            virtual int getOrder(void);
            // Sets the order
            virtual void setOrder(int order);
            // Tests whether it is a Variable
            virtual bool isVariable(void);
            // Tests whether it is a Function
            virtual bool isMacro(void);
            // Gets the scope where this symbol was declared
            virtual scope::Scope *getScope(void);
            // Sets the scope of this symbol
            virtual void setScope(scope::Scope *);
            // Prints this symbol
            virtual void dump(std::ostream &) = 0;

            virtual ~Symbol() {}
        };

        /* Variable Declaration.
        */
        class Variable : public Symbol {
        private:
            // the parameter flag
            bool is_parameter;
            // init value for global variable
            bool init;

        public:
            // Constructor
            Variable(std::string n, bool i, Location *l);
            // Sets the parameter flag
            void setParameter(void);
            // Tests whether it is a parameter
            bool isParameter(void);

            bool isInit(void);
            // Tests whether it is a global variable
            bool isGlobalVar(void);
            // Tests whether it is a local variable
            bool isLocalVar(void);
            // Tests whether this symbol is a Variable
            virtual bool isVariable(void);
            // Prints this symbol
            virtual void dump(std::ostream &os);
        };

        /* Function Definition.
        */
        class Macro : public Symbol {
        private:
            // the associated scope
            scope::MacroScope *associated;
            std::vector<Variable *> *parameters;
            std::vector<bool> *allocated;
            ast::MacroDef *owner;
            int allocatePos;
        public:
            // Constructor
            Macro(std::string n, ast::MacroDef *o, Location *l);
            // Gets the associated scope
            scope::MacroScope *getAssociatedScope(void);
            // Gets the result type
            // Gets the scope where this symbol was declared
            virtual scope::Scope *getScope(void);
            // Gets the type of this symbol
            virtual ExprType getType(void);
            // Appends a parameter to this function
            void appendParameter(Variable *);
            int numOfParameters(void);
            // Tests whether this symbol is a Function
            virtual bool isMacro(void);
            // Prints this symbol
            virtual void dump(std::ostream &os);

            ast::MacroDef *getOwner(void);

            void alloc_begin(void);
            void alloc_update(void);
            int alloc_first(void);
            int alloc_find(std::string);
            bool alloc_finish(void);
        };

    } // namespace symb
} // namespace GMAM

#endif // __GMAM_SYMBOL__
