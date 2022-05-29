/*****************************************************
 *
 *  Krain
 */

#include "builder/step.hpp"
#include <iostream>
using namespace GMAM;
using namespace GMAM::builder;

Step::Step() {pos = -1; content = "";}

Step::Step(int _pos) {pos = _pos; content = "";}

void Step::debug_print(std::ostream &os) {
    os << "(step: " << pos << " ";
    os << content;
    os << ")" << std::endl;
}



void Step::final_print(std::ostream &os) {
    final_print_intro(os);
    os << content;
    final_print_outro(os);
}

void Step::final_print_intro(std::ostream &os) {
    os 
        << "<entry>" << std::endl
        << "<step>" << pos << "</step>" << std::endl
        << "<event>" << std::endl
        << "<action>" << std::endl
        << "<libid>1</libid>" << std::endl
        << "<id>603</id>" << std::endl
        << "<kind>7</kind>" << std::endl
        << "<userelative>0</userelative>" << std::endl
        << "<isquestion>0</isquestion>" << std::endl
        << "<useapplyto>-1</useapplyto>" << std::endl
        << "<exetype>2</exetype>" << std::endl
        << "<functionname></functionname>" << std::endl
        << "<codestring></codestring>" << std::endl
        << "<whoName>self</whoName>" << std::endl
        << "<relative>0</relative>" << std::endl
        << "<isnot>0</isnot>" << std::endl
        << "<arguments>" << std::endl
        << "<argument>" << std::endl
        << "<kind>1</kind>" << std::endl
        << "<string>" << std::endl;
}

void Step::final_print_outro(std::ostream &os) {
    os 
        << "</string>" << std::endl
        << "</argument>" << std::endl
        << "</arguments>" << std::endl
        << "</action>" << std::endl
        << "</event>" << std::endl
        << "</entry>" << std::endl;
}