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
    using InsertOneResult = mongocxx::stdx::optional<mongocxx::result::insert_one>;
    using UpdateResult = mongocxx::stdx::optional<mongocxx::result::update>;
    using DeleteResult = mongocxx::stdx::optional<mongocxx::result::delete_result>;
    using FindResult = mongocxx::stdx::optional<mongocxx::cursor>;
    using FindOneResult = mongocxx::stdx::optional<bsoncxx::document::value>;

    extern mongocxx::instance instance;

    extern mongocxx::client globalClient;

    inline String dbName = "blog";

    class Model
    {
    public:
        int64_t id{};
        String createdAt;
        String updatedAt;

        [[nodiscard]] virtual bsoncxx::builder::stream::document toDocument() const = 0;

        [[nodiscard]] bsoncxx::builder::stream::document getModelDocument() const;

        static bsoncxx::types::b_date convertStringToBdate(const String &date);
    };

    class MongoModel
    {
    private:
        mongocxx::database db;

    public:
        virtual ~MongoModel() = default;

        mongocxx::collection getCollection();

        virtual String tableName() = 0;

        InsertOneResult insert(const Model &model);

        auto batchInsert(const Vector<bsoncxx::builder::stream::document> &list);

        UpdateResult update(int64_t id, const bsoncxx::builder::stream::document &document);

        DeleteResult deleteOne(int64_t id);

        DeleteResult deleteMany(const bsoncxx::builder::stream::document &filter);

        FindOneResult findOne(int64_t id);

        FindResult find(const bsoncxx::builder::stream::document &filter);

        void customOperator(const Function<void(mongocxx::collection &)> &func);

        int64_t countDocuments(const bsoncxx::builder::stream::document &filter);
    };

    extern void initMongodb(blog_backend::config::Config &c);
}

#endif //BLOG_BACKEND_COMMON_H
