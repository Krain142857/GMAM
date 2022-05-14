#ifndef __GMAM_TIMELINE__
#define __GMAM_TIMELINE__

#include "define.hpp"
#include <iostream>
#include <string>
#include <map>

namespace GMAM {

    #define GMAM_TIMELINE_DEFINED
    namespace builder {
        class Timeline {
        public:
            Timeline();
            Step *getStepPtr(int pos);
            void debug_print(std::ostream &os);
            void final_print(std::ostream &os);
            void final_print_intro(std::ostream &os);
            void final_print_outro(std::ostream &os);
        private:
            std::map<int, Step *> steps;
        };
    }
}

#endif