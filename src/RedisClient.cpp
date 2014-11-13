/*************************************************************************
	> File Name: RedisClient.cpp
	> Author: Melon
	> Mail:ymelon7@gmail.com 
	> Created Time: Thu 13 Nov 2014 01:13:56 AM PST
 ************************************************************************/
#include "RedisClient.h"
#include <string.h>
#include <muduo/base/Logging.h>
using namespace muduo;

RedisClient::RedisClient(const std::string &host, uint16_t port = 6379)
{
    connect_ = redisConnect(host.c_str(), port);

    if(connect_ == NULL || connect_->err)
    {
        LOG_ERROR << "redis connected host:" << host << " port: " << port;
        exit(EXIT_FAILURE);
    }else
    {
        LOG_INFO << "redis connect successfully.";
    }
}


RedisClient::~RedisClient()
{
    redisFree(connect_);
    LOG_INFO << "Redis Connection close.";
}


void RedisClient::setKeyValue(const std::string &key, const std::string &value)
{
    LOG_DEBUG << "Redis setKeyValue key: " << key 
               << " value: " << value;

    redisReply *reply = static_cast<redisReply*>
                        (redisCommand
                         (connect_, "set %s %s", key.c_str(), value.c_str()));  

    freeReplyObject(reply);
}


std::pair<std::string, bool> RedisClient::getValueByKey(const std::string &key)
{  
    LOG_DEBUG << "Redis getValueByKey key: " << key;

    redisReply *reply = static_cast<redisReply*>
                        (redisCommand
                         (connect_, "get %s", key.c_str()));

    std::pair<std::string, bool> ret;
    if(reply->type == REDIS_REPLY_NIL)
    {
        ret.second = false;
        LOG_DEBUG << "Redis getValueByKey key: " << key << " key is not exists";
    }else
    {
        ret.second = true;
        ret.first = reply->str;
        LOG_DEBUG << "Redis getValueByKey key: " << key << " value: " << ret.first;
    }

    freeReplyObject(reply);
    return ret;
}
