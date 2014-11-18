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

void QueryServer::onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp t)
{
    string s(buf->retrieveAllAsString());
    LOG_INFO << "receive php msg: " << s;

    std::string result = query_.queryWord(s.c_str());
    conn->send(result.c_str(), result.size());
}
