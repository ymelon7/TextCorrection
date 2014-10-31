#ifndef STRING_UTIL_H_
#define STRING_UTIL_H_

#include <string>

namespace stringutil
{
    void erasePunct(std::string &word);
    bool isAllDigit(const std::string &word);
    void stringToLower(std::string &word);
}


#endif //STRING_UTIL_H_
