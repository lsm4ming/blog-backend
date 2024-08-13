#include "cache/redis.h"

namespace blog_backend::cache
{
    sw::redis::ConnectionOptions connection_options;

    void initRedis(const blog_backend::config::Config &c)
    {
        connection_options.host = c.redis.host;
        connection_options.port = c.redis.port;
        if (!c.redis.password.empty()) // 设置密码
        {
            connection_options.password = c.redis.password;
        }
        auto client = sw::redis::Redis(connection_options);
        std::cout << "redis ping:" << client.ping() << std::endl;
    }
}