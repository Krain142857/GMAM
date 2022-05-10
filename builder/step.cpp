/*****************************************************
 *
 *  Krain
 */

#include "builder/step.hpp"
#include <iostream>
using namespace GMAM;
using namespace GMAM::builder;

Step::Step() {}

void Step::debug_print(std::ostream &os) {
    os << "(step: " << pos << " ";
    for (auto i : content) {
        os << i;
    }
    os << ")" << std::endl;
}



void Step::final_print(std::ostream &os) {
    final_print_intro(os);
    for (auto i : content) {
        os << i;
    }
    final_print_outro(os);
}

void Step::final_print_intro(std::ostream &os) {
    os << "<entry>" << std::endl;
    os << "<step>" << pos << "</step>" << std::endl;
    os << "<event>" << std::endl;
    os << "<action>" << std::endl;
    os << "<libid>1</libid>" << std::endl;
    os << "<id>603</id>" << std::endl;
    os << "<kind>7</kind>" << std::endl;
    os << "<userelative>0</userelative>" << std::endl;
    os << "<isquestion>0</isquestion>" << std::endl;
    os << "<useapplyto>-1</useapplyto>" << std::endl;
    os << "<exetype>2</exetype>" << std::endl;
    os << "<functionname></functionname>" << std::endl;
    os << "<codestring></codestring>" << std::endl;
    os << "<whoName>self</whoName>" << std::endl;
    os << "<relative>0</relative>" << std::endl;
    os << "<isnot>0</isnot>" << std::endl;
    os << "<arguments>" << std::endl;
    os << "<argument>" << std::endl;
    os << "<kind>1</kind>" << std::endl;
    os << "<string>" << std::endl;        
}

void Step::final_print_outro(std::ostream &os) {
    os << "</string>" << std::endl;
    os << "</argument>" << std::endl;
    os << "</arguments>" << std::endl;
    os << "</action>" << std::endl;
    os << "</event>" << std::endl;
    os << "</entry>" << std::endl;
}