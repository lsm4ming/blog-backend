#include "model/common.h"

namespace blog_backend::model
{
    std::once_flag init_flag;

    mongocxx::instance instance{};

    mongocxx::client globalClient{};

    void initMongodb(blog_backend::config::Config &c)
    {
        try
        {
            mongocxx::uri uri{
                    "mongodb://" + c.mongodb.username + ":" + c.mongodb.password + "@" + c.mongodb.host + ":" +
                    std::to_string(c.mongodb.port)};
            globalClient = mongocxx::client(uri);
            std::cout << "Connection successful!" << std::endl;
        } catch (const mongocxx::exception &e)
        {
            std::cerr << "MongoDB error: " << e.what() << std::endl;
        }
    }

    mongocxx::collection MongoModel::getCollection()
    {
        std::call_once(init_flag, [this]()
        {
            this->db = globalClient[dbName];
        });
        return this->db[this->tableName()];
    }

    auto MongoModel::insert(const bsoncxx::builder::stream::document &document)
    {
        auto collection = this->getCollection();
        return collection.insert_one(document.view());
    }
}