#ifndef CHINESE_FREQUENCY_H
#define CHINESE_FREQUENCY_H

#include <boost/noncopyable.hpp>
#include <string>
#include "../include/libjieba/MixSegment.hpp"

class ChineseFrequency : boost::noncopyable
{
    public:
        ChineseFrequency(std::string chFilename,
                         std::string stopListchFile,
                         std::string chDictFile,
                         std::string jiebaDictPath,
                         std::string jiebaModelPath);

        void readStopList();
        void readWordFile();
        void saveDict();

    private:
        std::string chFilename_;
        std::string stopListchFile_;
        std::string chDictFile_;
        
        //结巴分词使用
        std::string jiebaDictPath_;
        std::string jiebaModelPath_;

        CppJieba::MixSegment segment_;  //结巴分词

        std::unordered_map<std::string, int> words_;
        std::unordered_set<std::string> stopList_;
};


#endif //CHINESE_FREQUENCY_H
