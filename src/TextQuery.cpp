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


TextQuery::TextQuery(string enDictName, 
                     string chDictName,
                     const string &host,
                     uint16_t port)
    :enDictName_(move(enDictName)),
     chDictName_(move(chDictName)),
     client_(host, port)
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
        if(in.fail())  //处理错误
        {
            LOG_WARN << "En dict file format error in: " << enDictName_;
            in.clear();
            in.ignore(numeric_limits<streamsize> ::max(), '\n');
        }

        index_.addItem(make_pair(word, count));
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
            LOG_WARN << "Ch file format error in: " << chDictName_;
            in.clear();  //重置状态
            in.ignore(numeric_limits <streamsize> ::max(), '\n');
        }
        lines ++;
        
        index_.addItem(make_pair(word, count));
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
    //先查看缓存
    pair<string, bool> res = client_.getValueByKey(word);

    if(res.second)
    {
        return res.first;
    }
    else
    {
        string s = queryWordInDict(word);

        client_.setKeyValue(word, s);
        return s;
    }
}


string TextQuery::queryWordInDict(const string &word) const
{
   LOG_DEBUG << "query word: " << word;

   priority_queue<Word, vector<Word>, less<Word> > q;

   InvertedIndex::WordSet words = index_.getWords(word);
   for(const auto &pa : words)
   {
        int editdistance = editDistance(word, pa.first);
        if(static_cast<double>(editdistance) / word.size() < 0.5)
        {
            q.push(Word(pa.first, editdistance, pa.second)); 
        }
   }
   
   if(q.empty())
   {
       return string("");
   }
   else
       return q.top().word_;
}
