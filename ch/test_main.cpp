#include "ChineseFrequency.h"
#include <inttypes.h>
#include <muduo/base/Logging.h>
#include <string.h>
#include <sys/time.h>
#include <stdexcept>

using namespace std;

int64_t getUTime();

int main(int argc, char *argv[])
{
    ChineseFrequency wf("ch.txt",
                        "stopList.txt",
                        "../dict/ch.dict",
                        "../dict/jieba.dict.utf8",
                        "../dict/hmm_model.utf8");
   
    LOG_INFO << "Begin reading file";

    int64_t startTime = getUTime();
   
    wf.readStopList();
    wf.readWordFile();
    wf.saveDict();

    int64_t endTime = getUTime();

    LOG_INFO << "creat ch dict cost: " 
        << (endTime - startTime) / 1000 << "ms";
}

int64_t getUTime()
{
    struct timeval tv;
    ::memset(&tv, 0, sizeof tv);

    if(gettimeofday(&tv, NULL) == -1)
    {
        throw runtime_error("gettimeofday");
    }
    
    int64_t t = tv.tv_usec;
    t += tv.tv_sec * 1000 * 1000;
    
    return t;
}

