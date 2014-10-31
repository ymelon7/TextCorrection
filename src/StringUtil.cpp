#include "StringUtil.h"
#include <ctype.h>
#include <string.h>
#include <assert.h>

using namespace std;

namespace  //static
{

inline int minThribble(int a, int b, int c)
{
    int ret = (a < b) ? a : b;
    ret = (ret < c) ? ret : c;

    return ret;
}

}

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

int editDistance(const string &a, const string &b)
{
    assert(a.size() < 100 && b.size() < 100);        

    int memo[100][100];
    memset(memo, 0, sizeof memo);

    //L(i, 0) = i
    for(size_t i = 0; i <= a.size(); i ++)
        memo[i][0] = i;
    for(size_t j = 0; j <= b.size(); j ++)
        memo[0][j] = j;

    for(size_t i = 1; i <= a.size(); i ++)
    {
        for(size_t j = 1; j <= b.size(); j ++)
        {
            if(a[i - 1] == b[j - 1])
                memo[i][j] = memo[i - 1][j - 1];
            else
            {
                int t1 = memo[i - 1][j];
                int t2 = memo[i][j - 1];
                int t3 = memo[i - 1][j - 1];
                
                memo[i][j] = minThribble(t1, t2, t3) + 1;
            }
        
        }
    
    }

    return memo[a.size()][b.size()];
}

}
