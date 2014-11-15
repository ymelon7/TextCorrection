/*************************************************************************
	> File Name: RedisClient.cpp
	> Author: Melon
	> Mail:ymelon7@gmail.com 
	> Created Time: Thu 13 Nov 2014 01:13:56 AM PST
 ************************************************************************/
#include "RedisClient.h"
#include <string.h>
#include <muduo/base/Logging.h>
#include <memory>

using namespace muduo;

namespace
{
struct Delete    //删除器，用于后面的智能指针
{
public:
   void operator() (redisReply *reply) const
    {
        freeReplyObject(reply);
    }
};
}


RedisClient::RedisClient(const std::string &host, uint16_t port = 6379)
{
    connect_ = redisConnect(host.c_str(), port);

    if(connect_ == NULL || connect_->err)
    {
        LOG_FATAL << "redis connected host: " << host << " port: " << port;
    }
    else
    {
        LOG_INFO << "redis connect successfully.";
    }
}


RedisClient::~RedisClient()
{
    redisFree(connect_);
    LOG_INFO << "Redis Connection close.";
}


void RedisClient::setKeyValue(const std::string &key, const std::string &value) const
{
    LOG_DEBUG << "Redis setKeyValue key: " << key 
               << " value: " << value;

    std::unique_ptr<redisReply, Delete> reply(
        static_cast<redisReply *>(
            redisCommand(connect_, "get %s", key.c_str())),
        Delete());

    if(reply->type == REDIS_REPLY_ERROR)
    {
        LOG_ERROR << "Redis setKeyValue error, key= " << key << " value= " << value;
    }
}


std::pair<std::string, bool> RedisClient::getValueByKey(const std::string &key) const
{  
    LOG_DEBUG << "Redis getValueByKey, key: " << key;
    
    std::unique_ptr<redisReply, Delete> reply(
        static_cast<redisReply *>(
            redisCommand(connect_, "get %s", key.c_str())),
        Delete());

    if(reply->type == REDIS_REPLY_STRING)
    {
        LOG_DEBUG << "Redis getValueByKey, key: " << key << " value: " << reply->str;
        return make_pair(std::string(reply->str), true);
    }
    else if(reply->type ==REDIS_REPLY_NIL)
    {
        LOG_DEBUG << "Redis getValueByKey, key: " << key << " key is not exist";
        return make_pair(std::string(""), false);
    }
    else if(reply->type == REDIS_REPLY_ERROR)
    {
        LOG_FATAL << "The Redis command replied with an error"; 
    }
    else
    {
        LOG_FATAL << "The Redis command replied Unknown result";
    }

    return make_pair(std::string(""), false);
}
