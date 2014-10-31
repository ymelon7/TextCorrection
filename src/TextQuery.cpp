#include "TextQuery.h"
#include <fstream>
#include <stdexcept>
#include <muduo/base/Logging.h>

using namespace std;

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
    return "";    
}
