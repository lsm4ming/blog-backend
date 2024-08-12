#pragma once

#ifndef BLOG_BACKEND_CONFIG_H

#include <string>
#include <cpptools/common/singleton.h>
#include <cpptools/common/config.h>

namespace blog_backend::config
{
    class serverConfig
    {
    public:
        std::string host;
        std::uint16_t port{};
    };

    class mongoConfig
    {
    public:
        std::string host;
        std::uint16_t port{};
        std::string username;
        std::string password;
    };

    class redisConfig
    {
    public:
        std::string host;
        std::uint16_t port{};
        std::string password;
    };

    class Config
    {
    public:
        serverConfig server;
        mongoConfig mongodb;
        redisConfig redis;
    };

    extern Config &getConfig();

    extern void setConfig(const IniConfig &c);

    extern bool checkConfig();
}

#endif // BLOG_BACKEND_CONFIG_H
