/*************************************************************************
	> File Name: test_main.cpp
	> Author: Melon
	> Mail:ymelon7@gmail.com 
	> Created Time: Fri 31 Oct 2014 04:10:38 AM PDT
 ************************************************************************/

#include "TextQuery.h"
#include <iostream>
#include <muduo/base/Logging.h>
#include <muduo/base/Timestamp.h>

using namespace muduo;

int main (int argc, char *argv[])
{
   // Logger::setLogLevel(Logger::DEBUG); //设置日志打印级别

    TextQuery query("../dict/en.dict", 
                    "../dict/ch.dict",
                    "localhost", 6379);

    std::string word;
    while(std::cin >> word)
    {
        Timestamp t1(Timestamp::now());

        std::cout << query.queryWord(word) << std::endl;  

        Timestamp t2(Timestamp::now());

        std::cout << "query cost time: "<< timeDifference(t2, t1) << " s" << std::endl;
    }
}
