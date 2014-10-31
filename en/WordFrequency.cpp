#include "WordFrequency.h"
#include <fstream>
#include <stdexcept>
#include "StringUtil.h"
#include <algorithm>
#include <iostream>

using namespace std;
using namespace stringutil;

WordFrequency::WordFrequency(string fileName,
                             string stopFile,
                             string dictName)
    :fileName_(move(fileName)),
     stopFile_(move(stopFile)),
     dictName_(move(dictName))
{

}

void WordFrequency::readStopList()
{
   ifstream in(stopFile_.c_str()); 
   if(!in)
       throw runtime_error("open stopFile fail");

   string word;
   stopList_.clear();
   while(in >> word)
   {
        stopList_.insert(word);
   }

   in.close();
}

void WordFrequency::readWordFile()
{
    ifstream in(fileName_.c_str());
    if(!in)
        throw runtime_error("open file fail");

    string word;
    words_.clear();
    while(in >> word)
    {
        erasePunct(word);
        if(isAllDigit(word))
            continue;
        if(word.empty())      //to deal with "blank , blank" in en.txt,
            continue;
        stringToLower(word);
        if(0 == stopList_.count(word)) //not stopword
            words_[word] ++;
    }

    in.close();
}

void WordFrequency::saveDict() const
{
   ofstream of(dictName_.c_str());
   if(!of)
        throw runtime_error("open dictfile fail");

   for(auto it = words_.begin(); 
       it != words_.end(); 
       it ++)
   {
        of << it->first << " " << it->second << endl;
   }

   of.close();
}


