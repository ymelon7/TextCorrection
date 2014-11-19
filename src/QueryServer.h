#ifndef QUERY_SERVER_H
#define QUERY_SERVER_H

#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>
#include <muduo/base/Timestamp.h>
#include <muduo/base/ThreadPool.h>
#include <string>
#include "TextQuery.h"

class QueryServer : boost::noncopyable
{
public:
    QueryServer(const std::string &enDict,
                const std::string &chDict,
                const std::string &redisHost,
                uint16_t port,
                muduo::net::EventLoop *loop,
                const muduo::net::InetAddress &addr);

    void start()
    {
        pool_.start(4);
        server_.start();
    }

private:
   void onMessage(const muduo::net::TcpConnectionPtr &conn, 
                  muduo::net::Buffer *buf, 
                  muduo::Timestamp t); 
    
   void queryWord(const std::string &word, 
                  const muduo::net::TcpConnectionPtr &conn);

    TextQuery query_;
    muduo::net::TcpServer server_;
    muduo::ThreadPool pool_;
};


#endif //QUERY_SERVER_H
