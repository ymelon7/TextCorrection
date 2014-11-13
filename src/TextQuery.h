#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H

#include <string>
#include <unordered_map>
#include <boost/noncopyable.hpp>

class TextQuery : boost::noncopyable
{
    public:
        TextQuery(std::string enDictName, std::string chDictName);
        std::string queryWord(const std::string &word) const;

    private:
        void readEnDict();   //read english dict       
        void readChDict();   //read chinese dict

        std::string enDictName_;    //en dict file
        std::string chDictName_;    //ch dict file
        std::unordered_map<std::string, int> enDict_;   //en dict
};


#endif //TEXT_QUERY_H
