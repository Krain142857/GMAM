/*****************************************************
 *  Implementation of the "ASTNode" abstract class.
 *
 *  Keltin Leung 
 */

#include "ast/ast.hpp"
#include "location.hpp"
#include <iostream>

using namespace GMAM;
using namespace GMAM::ast;

/*  Names of the AST nodes.
 *
 *  NOTE: The order of node_name's must be the same with that of NodeType's.
 */
const char *ASTNode::node_name[] = {
    "Program", 
    "VarDef",
    "MacroDef",
    "Step",
    "InitArgu",
    "CompExpr",
    "Interval",
    "SingleInt", 
    "RawString",
    "VarExpr",
    "MacroExpr",
    "IfExpr",
    "EquExpr",
    };

/*  Whether to print the decorated abstract syntax tree.
 */
bool print_decorated_ast = false;

/*  Sets the basic information of a node.
 *
 *  PARAMETERS:
 *    k     - the node kind
 *    l     - position in the source text
 */
void ASTNode::setBasicInfo(NodeType k, Location *l) {
    kind = k;
    loc = l;
}

/*  Gets the node kind.
 *
 *  RETURNS:
 *    the node kind
 */
ASTNode::NodeType ASTNode::getKind(void) { return kind; }

/*  Gets the source text location of this node
 *
 *  RETURNS:
 *    the source text location
 */
Location *ASTNode::getLocation(void) { return loc; }

/*  Dumps this node to an output stream.
 *
 *  PARAMETERS:
 *    os    - the output stream
 */
void ASTNode::dumpTo(std::ostream &os) {
    os << "(" << node_name[kind];
}

/*  Outputs an ASTNode.
 *
 *  PARAMETERS:
 *    os    - the output stream
 *    p     - the ASTNode
 *  RETURNS:
 *    the output stream
 */
std::ostream &GMAM::operator<<(std::ostream &os, ASTNode *p) {
    if (p == NULL)
        os << "!!NULL!!";
    else
        p->dumpTo(os);
    return os;
}


/*  Outputs a FuncList.
 *
 *  PARAMETERS:
 *    os    - the output stream
 *    l     - the Func list
 *  RETURNS:
 *    the output stream
 */
std::ostream &GMAM::operator<<(std::ostream &os, ASTList *l) {
    os << "[";
    if (!l->empty()) {
        os << " ";
        auto it = l->begin();
        os << *it;
        while (++it != l->end()) {
            os << *it;
        }
    }
    os << "]";

    return os;
};


/*  Outputs a FuncList.
 *
 *  PARAMETERS:
 *    os    - the output stream
 *    l     - the Func list
 *  RETURNS:
 *    the output stream
 */
std::ostream &GMAM::operator<<(std::ostream &os, ExprList *l) {
    os << "[";
    if (!l->empty()) {
        os << " ";
        auto it = l->begin();
        os << *it;
        while (++it != l->end()) {
            os << *it;
        }
    }
    os << "]";

    return os;
};

std::ostream &GMAM::operator<<(std::ostream &os, VarList *l) {
    os << "[";
    if (!l->empty()) {
        os << " ";
        auto it = l->begin();
        os << *it;
        while (++it != l->end()) {
            os << *it;
        }
    }
    os << "]";

    return os;
};

std::ostream &GMAM::operator<<(std::ostream &os, ArguList *l) {
    os << "[";
    if (!l->empty()) {
        os << " ";
        auto it = l->begin();
        os << *it;
        while (++it != l->end()) {
            os << *it;
        }
    }
    os << "]";

    return os;
};

std::ostream &GMAM::operator<<(std::ostream &os, ExprType e) {
    switch (e) {
    case NULL_E:
        os << "NULL_E";
        break;
    case INT_E:
        os << "INT_E";
        break;
    case STRING_E:
        os << "STRING_E";
        break;
    case INTERVAL_E:
        os << "INTERVAL_E";
        break;
    case ERROR_E:
        os << "ERROR_E";
        break;
    
    default:
        break;
    }

    return os;
};