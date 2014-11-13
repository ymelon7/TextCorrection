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


int getLenOfUTF8(unsigned char c)
{
    int cnt = 0;
    while(c & (1 << (7 - cnt)))
    {
        cnt ++; 
    }
    
    return cnt;
}


int editDistanceUint_32(const vector<uint32_t> &w1,
                        const vector<uint32_t> &w2)
{
    int len_a = w1.size();
    int len_b = w2.size();

    int memo[100][100];
    memset(memo, 0, sizeof memo);

    for(int i = 0; i <= len_a; i ++)
        memo[i][0] = i;
    for(int j = 0; j <= len_b; j ++)
        memo[0][j] = j;

    for(int i = 1; i <= len_a; i ++)
    {
        for(int j = 1; j <= len_b; j ++)
        {
            if(w1[i - 1] == w2[j - 1])
            {
                memo[i][j] = memo[i - 1][j - 1];
            }
            else
            {
                int t1 = memo[i - 1][j];
                int t2 = memo[i][j - 1];
                int t3 = memo[i - 1][j - 1];
                
                memo[i][j] = minThribble(t1, t2, t3) + 1;
            } 
        } 
    }

    return memo[len_a][len_b];
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


//原始的英文单词编辑距离计算
int editDistanceStr(const string &a, const string &b)
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
            {
                memo[i][j] = memo[i - 1][j - 1];
            }
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


//把字符串解析成uint32_t数组
void parseUTF8String(const string &s, vector<uint32_t> &vec)
{
    vec.clear(); 
    for(string::size_type ix = 0; ix != s.size(); ix ++)
    {
        assert(ix < s.size());
    
        int len = getLenOfUTF8(s[ix]);
        uint32_t t = (unsigned char)s[ix]; //e5 ?

        if(len > 1)
        {
            len --;
            //拼接剩余的字节
            while(len --)
            {
                t = (t << 8) | s[++ix];
            } 
        }

        vec.push_back(t);
    }
}



int editDistance(const string &a, const string &b)
{
    vector<uint32_t> w1;
    vector<uint32_t> w2;
    
    parseUTF8String(a, w1);
    parseUTF8String(b, w2);
    
    int ret = editDistanceUint_32(w1, w2);

    return  ret;
}

}
