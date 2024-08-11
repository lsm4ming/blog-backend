#ifndef BLOG_BACKEND_COMMON_H
#define BLOG_BACKEND_COMMON_H

#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/database.hpp>
#include <mutex>
#include "config/config.h"

/**
docker run -d \
  --name mongodb \
  -e MONGO_INITDB_ROOT_USERNAME=admin \
  -e MONGO_INITDB_ROOT_PASSWORD=admin123456 \
  -p 27017:27017 \
  mongo
 */
namespace blog_backend::model
{
    extern mongocxx::instance instance;

    extern mongocxx::client globalClient;

    constexpr const char *DB_NAME = "blog";

    extern void initMongodb(blog_backend::config::Config &c);
}

#endif //BLOG_BACKEND_COMMON_H
