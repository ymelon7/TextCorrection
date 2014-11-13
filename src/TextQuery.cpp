#include "TextQuery.h"
#include "StringUtil.h"
#include <fstream>
#include <muduo/base/Logging.h>
#include <vector>
#include <queue>
#include <limits>

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


TextQuery::TextQuery(string enDictName, string chDictName)
    :enDictName_(move(enDictName)),
     chDictName_(move(chDictName))
{
   readEnDict();
   readChDict();
}

void TextQuery::readEnDict()
{
    ifstream in(enDictName_.c_str());
    if(!in)
        LOG_FATAL << "open endict failed";
    
    LOG_INFO << "Begin reading endict";

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
        LOG_FATAL << "enDict Format error";
    
    LOG_INFO << "read enDict over";

    in.close();
}


void TextQuery::readChDict()
{
    ifstream in(chDictName_);
    if(!in)
    {
        LOG_FATAL << "open chdict fjle erroe";
    }

    LOG_INFO << "Begin reading chdict" << chDictName_;

    string word;
    int count;
    int lines = 0;
    while(in >> word >> count, !in.eof())
    {
        if(in.fail())
        {
            in.clear();  //重置状态
            in.ignore(numeric_limits <streamsize> ::max(), '\n');
        }
        lines ++;
        
        //这里把中文也和英文一样放到同一个map中
        pair<unordered_map<string, int>::iterator, bool> ret = 
            enDict_.insert(make_pair(word, count));
        assert(ret.second); (void)ret; 
    }

    LOG_DEBUG << "read chdict: " << lines << "lines";

    if(!in.eof())  //判断是否是文件格式错误
    {
        LOG_FATAL << "file format error";
    }
    
    LOG_INFO << "read chDict finished";

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



