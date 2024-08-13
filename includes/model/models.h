#ifndef BLOG_BACKEND_MODELS_H
#define BLOG_BACKEND_MODELS_H

#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/database.hpp>
#include <cpptools/common/common.h>
#include <mutex>
#include "common.h"

namespace blog_backend::model
{
    using namespace cpptools::common;

    using String = std::string;
    using InsertOneResult = mongocxx::stdx::optional<mongocxx::result::insert_one>;
    using UpdateResult = mongocxx::stdx::optional<mongocxx::result::update>;
    using DeleteResult = mongocxx::stdx::optional<mongocxx::result::delete_result>;
    using FindResult = mongocxx::stdx::optional<mongocxx::cursor>;
    using FindOneResult = mongocxx::stdx::optional<bsoncxx::document::value>;

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
        virtual ~MongoModel()
        {
            std::cout << "~MongoModel" << std::endl;
        }

        mongocxx::collection getCollection();

        virtual String tableName() = 0;

        InsertOneResult insert(const Model &model);

        auto batchInsert(const Vector<bsoncxx::builder::stream::document> &list);

        UpdateResult update(int64_t id, const bsoncxx::builder::stream::document &document);

        DeleteResult deleteOne(int64_t id);

        DeleteResult deleteMany(const bsoncxx::builder::stream::document &filter);

        FindOneResult findOne(int64_t id);

        FindResult findAll();

        FindResult find(const bsoncxx::builder::stream::document &filter);

        void customOperator(const Function<void(mongocxx::collection &)> &func);

        int64_t countDocuments(const bsoncxx::builder::stream::document &filter);
    };
}

#endif //BLOG_BACKEND_MODELS_H
