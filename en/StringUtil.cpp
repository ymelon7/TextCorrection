#include "StringUtil.h"
#include <ctype.h>

using namespace std;

namespace stringutil
{

void erasePunct(string &word)
{
    string::iterator it = word.begin();
    while(it != word.end())
    {
        if(ispunct(*it))
            it = word.erase(it);
        else
            ++ it; 
    } 
}

bool isAllDigit(const string &word)
{
    for(string::const_iterator it = word.begin();
        it != word.end();
        it ++)
    {
        if(!isdigit(*it))
            return false;
    }

    return true;
}

void stringToLower(string &word)
{
    for(string::iterator it = word.begin();
        it != word.end();
        it ++)
    {
        if(isupper(*it))
            *it = tolower(*it);
    }
}

}
