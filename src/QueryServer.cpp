#include "QueryServer.h"
#include <muduo/base/Logging.h>

using namespace muduo;
using namespace muduo::net;
using namespace std::placeholders;

QueryServer::QueryServer(const std::string &enDict,
                         const std::string &chDict,
                         const std::string &redisHost,
                         uint16_t port,
                         EventLoop *loop,
                         const InetAddress &addr)
    :query_(enDict, chDict, redisHost, port),
     server_(loop, addr, "QueryServer")
{
    server_.setMessageCallback(std::bind(&QueryServer::onMessage, this, _1, _2, _3));
}


void QueryServer::onMessage(const TcpConnectionPtr &conn, 
                            Buffer *buf, 
                            Timestamp t)
{
    string s(buf->retrieveAllAsString());
    LOG_INFO << "receive php msg: " << s;
   
    std::string s2(s.c_str());
    pool_.run(
            std::bind(
                &QueryServer::queryWord, this, s2, conn));

}

//把单词的查询和结果的回发交给线程池
void QueryServer::queryWord(const std::string &word,
                            const TcpConnectionPtr &conn)
{
    std::string result = query_.queryWord(word);
    conn->send(result.c_str(), result.size());
}
