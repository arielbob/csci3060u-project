#include <sstream>
#include <iomanip>
#include "util.h"

using namespace std;

/**
* Trims whitespace from a string
* @param str String to be trimmed
* @return The trimmed string
*/
string util::trim_str(string str) {
    int start = -1;
    int end = -1;
    for (unsigned int i = 0; i < str.size(); i++) {
        if (start < 0 && str[i] != ' ') start = i;
        if (str[i] != ' ') end = i + 1;
    }
    int len = end - start;

    if (start > -1) {
        return str.substr(start, len);
    } else {
        // FIXME (arielbob): I think we should return an empty string here instead
        return str;
    }
}

/**
* Pad a string from the left
* @param str String to pad
* @param len Size of padded string
* @param fill_char Character to fill padding with
* @return The padded string
*/
string util::left_pad(string str, size_t len, char fill_char) {
    if (str.size() >= len) return str.substr(0, len);

    int pad_len = len - str.size();
    string padding(pad_len, fill_char);

    stringstream ss;
    ss << padding << str;

    return ss.str();
}

/**
* Pad a string from the right
* @param str String to pad
* @param len Size of padded string
* @param fill_char Character to fill padding with
* @return The padded string
*/
string util::right_pad(string str, size_t len, char fill_char) {
    if (str.size() >= len) return str.substr(0, len);

    int pad_len = len - str.size();
    string padding(pad_len, fill_char);

    stringstream ss;
    ss << str << padding;

    return ss.str();
}

/**
* Create credit string from double
* @param credit The credit amount
* @param len Size of final credit string
* @return Padded credit string
*/
string util::credit_str(double credit, size_t len) {
    stringstream ss;
    ss << fixed << setprecision(2) << credit;

    string ret = ss.str();
    if (ret.size() < len) return left_pad(ret, len, '0');
    return ret;
}