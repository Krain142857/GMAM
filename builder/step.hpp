#ifndef __GMAM_STEP__
#define __GMAM_STEP__

#include "define.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace GMAM {

    #define GMAM_STEP_DEFINED
    namespace builder {
        struct Step {
            int pos;
            std::vector<std::string> content;
            Step();
            Step(int _pos);
            void debug_print(std::ostream &os);
            void final_print(std::ostream &os);
            void final_print_intro(std::ostream &os);
            void final_print_outro(std::ostream &os);
        };
    }
}

#endif