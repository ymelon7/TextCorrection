#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <boost/noncopyable.hpp>
#include <set>
#include <unordered_map>
#include <string>
#include <stdint.h>

class InvertedIndex : boost::noncopyable
{
public:
    typedef std::pair<std::string, int> WordItem;
    typedef std::set<WordItem> WordSet;

    void addItem(WordItem item);  //C++11
    WordSet getWords(const std::string &s) const;

private:
    //uint32_t -> WordSet   包含单词的数组
    typedef std::unordered_map<uint32_t, WordSet> Index;
    Index index_;
};


#endif //INVERTED_INDEX_H
