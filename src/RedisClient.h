/*************************************************************************
	> File Name: RedisClient.h
	> Author: Melon
	> Mail:ymelon7@gmail.com 
	> Created Time: Thu 13 Nov 2014 01:07:11 AM PST
 ************************************************************************/
#ifndef REDIS_CLIENT_H
#define REDIS_CLIENT_H

#include <boost/noncopyable.hpp>
#include <hiredis.h>
#include <string>

class RedisClient : boost::noncopyable
{
 public:
    RedisClient(const std::string &host, uint16_t port);
    ~RedisClient();

    void setKeyValue(const std::string &key, const std::string &value) const;
    std::pair<std::string, bool> getValueByKey(const std::string &key) const;

 private:
    redisContext *connect_;
};


#endif //REDIS_CLIENT_H
