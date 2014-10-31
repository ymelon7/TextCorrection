/*************************************************************************
	> File Name: test_main.cpp
	> Author: Melon
	> Mail:ymelon7@gmail.com 
	> Created Time: Thu 30 Oct 2014 06:44:02 PM PDT
 ************************************************************************/

#include "WordFrequency.h"
#include <iostream>
#include <inttypes.h>
#include <muduo/base/Logging.h>
#include <string.h>
#include <stdexcept>
#include <sys/time.h>

using namespace std;

int64_t getUtime();

int main (int argc, char *argv[])
{
    WordFrequency wf("en.txt", "stopList.txt", "../dict/en.dict");
    LOG_INFO << "start reading files";
    int64_t startTime = getUtime();

    wf.readStopList();
    wf.readWordFile();
    wf.saveDict();

    int64_t endTime = getUtime();
    LOG_INFO << "creat english dict cost time: " 
        << (endTime - startTime) / 1000 << "ms";
}

int64_t getUtime()
{
    struct timeval tv;
    ::memset(&tv, 0, sizeof tv);
    if(::gettimeofday(&tv, NULL) == -1)
        throw runtime_error("gettimeofday");

    int64_t t = tv.tv_usec;
    t += tv.tv_sec *1000 * 1000;
    
    return t;
}

