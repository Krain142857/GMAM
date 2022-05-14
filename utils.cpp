#include "utils.hpp"

std::string standard_output(const char *s) {
    std::string input = s;
    int t = input.find_last_of('/');
    int name_begin = t == std::string::npos ? 0 : t + 1;
    input = input.substr(name_begin);
    t = input.find_last_of('.');
    int name_end = t == std::string::npos ? input.length() : t;
    input = input.substr(0, name_end);
    return std::string("./output/") + input + std::string(".timeline.gmx");
}