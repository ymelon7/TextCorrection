/*************************************************************************
	> File Name: test_main.cpp
	> Author: Melon
	> Mail:ymelon7@gmail.com 
	> Created Time: Fri 31 Oct 2014 04:10:38 AM PDT
 ************************************************************************/
#include "QueryServer.h"
#include <muduo/base/Logging.h>
#include <muduo/base/Timestamp.h>

using namespace muduo;
using namespace muduo::net;

int main (int argc, char *argv[])
{
   // Logger::setLogLevel(Logger::DEBUG); //设置日志打印级别

    TextQuery query("../dict/en.dict", 
                    "../dict/ch.dict",
                    "localhost", 6379);

    EventLoop loop;
    InetAddress addr("localhost", 9981);
    QueryServer server("../dict/en.dict",
                       "../dict/ch.dict",
                       "localhost", 6379,
                       &loop,
                       addr);
    
    server.start();
    loop.loop();
}
