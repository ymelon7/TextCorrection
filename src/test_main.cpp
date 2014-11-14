/*************************************************************************
	> File Name: test_main.cpp
	> Author: Melon
	> Mail:ymelon7@gmail.com 
	> Created Time: Fri 31 Oct 2014 04:10:38 AM PDT
 ************************************************************************/

#include "TextQuery.h"
#include <iostream>
#include <muduo/base/Logging.h>

using namespace muduo;

int main (int argc, char *argv[])
{
    Logger::setLogLevel(Logger::DEBUG); //设置日志打印级别

    TextQuery query("../dict/en.dict", 
                    "../dict/ch.dict",
                    "localhost", 6379);

    std::string word;
    while(std::cin >> word)
    {
        std::cout << query.queryWord(word) << std::endl;  
    }
}
