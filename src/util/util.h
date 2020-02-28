#ifndef UTIL_H
#define UTIL_H

#include <string>

namespace util {
    /*
    * Trims whitespace from a string
    */
    std::string trim_str(std::string str);
    /*
    * Pad a string from the left
    */
    std::string left_pad(std::string str, size_t len, char fill_char);
    /*
    * Pad a string from the right
    */
    std::string right_pad(std::string str, size_t len, char fill_char);
    /*
    * Create credit string from double
    */
    std::string credit_str(double credit, size_t len);

    bool isNumber(std::string s);
}

#endif
