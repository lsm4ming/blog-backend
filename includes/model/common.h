#ifndef BLOG_BACKEND_COMMON_H
#define BLOG_BACKEND_COMMON_H

#include "config/config.h"
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/database.hpp>
#include <mutex>

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

    inline String dbName = "blog";

    class Model
    {
    public:
        int64_t id;
        String createdAt;
        String updatedAt;
    };

    class MongoModel
    {
    private:
        mongocxx::database db;

    public:
        virtual ~MongoModel() = default;

        mongocxx::collection getCollection();

        virtual String tableName() = 0;

        auto insert(const bsoncxx::builder::stream::document &document);
    };

    extern void initMongodb(blog_backend::config::Config &c);
}

#endif //BLOG_BACKEND_COMMON_H
