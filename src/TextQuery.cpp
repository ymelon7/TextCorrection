#include "TextQuery.h"
#include "StringUtil.h"
#include <fstream>
#include <stdexcept>
#include <muduo/base/Logging.h>
#include <vector>
#include <queue>

using namespace std;
using namespace stringutil;

namespace
{

struct Word
{
    public:
        Word(string word,
             int editDistance,
             int frequency)
            :word_(move(word)),
             editDistance_(editDistance),
             frequency_(frequency)
         {
    
         }

    public:
        string word_;
        int editDistance_;
        int frequency_;
};

bool operator<(const Word &a, const Word &b)
{
    if(a.editDistance_ != b.editDistance_)
        return a.editDistance_ > b.editDistance_;

    return a.frequency_ < b.frequency_;
}

}


TextQuery::TextQuery(string enDictName)
    :enDictName_(move(enDictName))
{
   readEnDict();
}

void TextQuery::readEnDict()
{
    ifstream in(enDictName_.c_str());
    if(!in)
        throw runtime_error("read en dict fail");
    
    string word;
    int count = 0;
    while(in >> word >> count)
    {
       pair<unordered_map<string, int>::iterator, bool> ret =
           enDict_.insert(make_pair(word, count));
       assert(ret.second);  //ensure insert success
       (void)ret;     //to remove compile worning
    
    }
  
    if(!in.eof())   //check if enDict file format error
        throw runtime_error("enDict Format error");
    
    LOG_INFO << "read enDict over";

    in.close();
}

string TextQuery::queryWord(const string &word) const
{
    priority_queue<Word, vector<Word>, less<Word> > q;
    LOG_DEBUG << "query word: " << word;

    for(const auto &pa : enDict_)
    {
        int edit = editDistance(word, pa.first);
        q.push(Word(pa.first, edit, pa.second)); 
    }

    return q.top().word_;
}



