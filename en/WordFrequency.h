#ifndef WORD_FREQUENCY_H
#define WORD_FREQUENCY_H

#include <boost/noncopyable.hpp>
#include <string>
#include <unordered_map>
#include <unordered_set>

class WordFrequency : boost::noncopyable
{
    public:
        WordFrequency(std::string fileName,
                      std::string stopFile,
                      std::string dictName);

        void readStopList();
        void readWordFile();

        void saveDict() const;
    private:
        std::string fileName_;
        std::string stopFile_;
        std::string dictName_;

        std::unordered_map<std::string, int> words_;
        std::unordered_set<std::string> stopList_;
};


#endif //WORD_FREQUENCY_H
