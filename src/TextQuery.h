#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H

#include <string>
#include <unordered_map>
#include <boost/noncopyable.hpp>
#include "RedisClient.h"

class TextQuery : boost::noncopyable
{
    public:
        TextQuery(std::string enDictName, 
                  std::string chDictName,
                  const std::string &host,
                  uint16_t port);
        std::string queryWord(const std::string &word) const;

    private:
        void readEnDict();   //read english dict       
        void readChDict();   //read chinese dict
        
        std::string queryWordInDict(const std::string &word) const;  //执行真正的查询
        

        std::string enDictName_;    //en dict file
        std::string chDictName_;    //ch dict file

        std::unordered_map<std::string, int> enDict_;   //en dict

        RedisClient client_;   //redis
};


#endif //TEXT_QUERY_H
