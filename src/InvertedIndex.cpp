#include "InvertedIndex.h"
#include "StringUtil.h"

using namespace std;

void InvertedIndex::addItem(WordItem item)
{
    //深圳市 20
    //1.解析字符串
    vector<uint32_t> chars;
    stringutil::parseUTF8String(item.first, chars);

    //2.依次加入 深 圳 市
    for(uint32_t t : chars)
    {
        index_[t].insert(move(item));
    }
}


InvertedIndex::WordSet InvertedIndex::getWords(const string &s) const
{
    WordSet result;
    //1.解析字符串
    vector<uint32_t> chars;
    stringutil::parseUTF8String(s, chars);

    //2. .依次取出单词的set 然后合并
    for(uint32_t t : chars)
    {
        Index::const_iterator it = index_.find(t);
        if(it != index_.end())
        {
            //uint32_t -> WordSet
            const WordSet &words = it->second;
            result.insert(words.begin(), words.end());
        }
    }

    return result;
}
