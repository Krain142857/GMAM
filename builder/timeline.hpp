#ifndef __GMAM_TIMELINE__
#define __GMAM_TIMELINE__

#include "define.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace GMAM {

    #define GMAM_TIMELINE_DEFINED
    namespace builder {
        class Timeline {
        public:
            Timeline();
            void append(Step *s);
            void debug_print(std::ostream &os);
            void final_print(std::ostream &os);
            void final_print_intro(std::ostream &os);
            void final_print_outro(std::ostream &os);
        private:
            std::vector<Step *> steps;
        };
    }
}

#endif