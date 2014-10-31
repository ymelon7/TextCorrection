#ifndef STRING_UTIL_H_
#define STRING_UTIL_H_

#include <string>

namespace stringutil
{
    void erasePunct(std::string &word);
    bool isAllDigit(const std::string &word);
    void stringToLower(std::string &word);
    int editDistance(const std::string &a, const std::string &b);
}


#endif //STRING_UTIL_H_
