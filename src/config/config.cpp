#include "config/config.h"
#include "model/config.h"


namespace blog_backend::config
{
    constexpr const char *DEFAULT_HOST = "127.0.0.1";
    constexpr const char *DEFAULT_PORT = "8080";

    Config &getConfig()
    {
        auto c = Singleton<Config>::getInstance();
        return *c;
    }

    void setConfig(const IniConfig &c)
    {
        auto config = Singleton<Config>::getInstance();
        config->server.host = c.getStrValue("server", "host", "");
        config->server.port = c.getIntValue("server", "port", 0);

        config->mongodb.host = c.getStrValue("mongodb", "host", "");
        config->mongodb.port = c.getIntValue("mongodb", "port", 0);
        config->mongodb.username = c.getStrValue("mongodb", "username", "");
        config->mongodb.password = c.getStrValue("mongodb", "password", "");

        config->redis.host = c.getStrValue("redis", "host", "");
        config->redis.port = c.getIntValue("redis", "port", 0);
        config->redis.password = c.getStrValue("redis", "password", "");
    }

    bool checkConfig()
    {
        auto config = Singleton<Config>::getInstance();
        if (config->mongodb.host.empty())
        {
            perror("mongodb host is empty");
            return false;
        }
        if (config->mongodb.port == 0)
        {
            perror("mongodb port is empty");
            return false;
        }
        if (config->redis.host.empty())
        {
            perror("redis host is empty");
            return false;
        }
        if (config->redis.port == 0)
        {
            perror("redis port is empty");
            return false;
        }
        if (config->server.host.empty())
        {
            config->server.host = DEFAULT_HOST;
        }
        if (config->server.port == 0)
        {
            config->server.port = std::strtol(DEFAULT_PORT, nullptr, 10);
        }
        return true;
    }
}