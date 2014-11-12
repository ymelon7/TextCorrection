#include "ChineseFrequency.h"
#include <muduo/base/Logging.h>
#include <fstream>
#include <vector>

using namespace std;
using namespace CppJieba;

ChineseFrequency::ChineseFrequency(string chFilename,
                                   string stopListchFile,
                                   string chDictFile,
                                   string jiebaDictPath,
                                   string jiebaModelPath)
    :chFilename_(move(chFilename)),
     stopListchFile_(move(stopListchFile)),
     chDictFile_(move(chDictFile)),
     jiebaDictPath_(move(jiebaDictPath)),
     jiebaModelPath_(move(jiebaModelPath)),
     segment_(jiebaDictPath_,jiebaModelPath_)
{
    LOG_INFO << "jieba分词启动";
}

void ChineseFrequency::readStopList()
{
    ifstream in(stopListchFile_);     //why? c.str()?
    if(!in)
        LOG_FATAL << "open stopListch file error";

    string word;
    while(in >> word)
    {
        stopList_.insert(word); 
    }
    if(!in.eof())  //error, not read all of the file
        LOG_FATAL << "read stopList ch error";
    
    in.close();
}

void ChineseFrequency::readWordFile()
{
    ifstream in(chFilename_);
    if(!in)
        LOG_FATAL << "open chFile error";

    string line;
    vector<string> result;  //存放分词结果
    while(getline(in, line))
    {
        result.clear();
        segment_.cut(line, result);

        for(const string &s : result)
        {
            if(stopList_.count(s) == 0)
                words_[s] ++; 
        }
    }
    if(!in.eof())
        LOG_FATAL << "read chFile error";

    in.close();
}

void ChineseFrequency::saveDict()
{
    ofstream of(chDictFile_);
    if(!of)
        LOG_FATAL << "open chDictfile error";

    for(auto it = words_.begin();
        it != words_.end();
        it ++)
    {
        of << it ->first << " " << it ->second << endl; 
    }
   
    of.close();
}


