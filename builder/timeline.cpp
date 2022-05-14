/*****************************************************
 *
 *  Krain
 */

#include "builder/timeline.hpp"
#include "builder/step.hpp"
using namespace GMAM;
using namespace GMAM::builder;

Timeline::Timeline() {}

Step *Timeline::getStepPtr(int pos) {
    auto it = steps.find(pos);
    if (it != steps.end()) return (*it).second;
    else {
        Step *newStep = new Step(pos);
        steps[pos] = newStep;
        return newStep;
    }
}

void Timeline::debug_print(std::ostream &os) {
    os << "[";
    for (auto i : steps) {
        i.second->debug_print(os);
    }
    os << "]" << std::endl;
}

void Timeline::final_print(std::ostream &os) {
    final_print_intro(os);
    for (auto i : steps) {
        i.second->final_print(os);
    }
    final_print_outro(os);
}

void Timeline::final_print_intro(std::ostream &os) {
    os 
        << "<!--This Document is generated by GameMaker, if you edit it by hand then you do so at your own risk!-->" << std::endl
        << "<timeline>" << std::endl;
}

void Timeline::final_print_outro(std::ostream &os) {
    os 
        << "</timeline>" << std::endl;
}