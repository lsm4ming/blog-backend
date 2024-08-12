#ifndef BLOG_BACKEND_REDIS_H
#define BLOG_BACKEND_REDIS_H

#include <cpptools/common/common.h>
#include <sw/redis++/redis++.h>
#include <cpptools/common/config.h>
#include <iostream>
#include "config/config.h"

using namespace cpptools::common;

namespace blog_backend::cache
{
    extern sw::redis::ConnectionOptions connection_options;

    extern void initRedis(const blog_backend::config::Config &c);
}

#endif //BLOG_BACKEND_REDIS_H
