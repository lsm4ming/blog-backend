#include "model/common.h"

namespace blog_backend::model
{
    HashMap<String, std::once_flag> init_flag_map;

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
//        auto t = init_flag_map.find(this->tableName());
//        if (t == init_flag_map.end())
//        {
//            std::call_once(init_flag_map[this->tableName()], [this]()
//            {
//                this->db = globalClient[dbName];
//            });
//        }
        std::call_once(init_flag_map[this->tableName()], [this]()
        {
            this->db = globalClient[dbName];
        });
        return this->db[this->tableName()];
    }

    InsertOneResult MongoModel::insert(const Model &model)
    {
        auto collection = this->getCollection();
        return collection.insert_one(model.toDocument().view());
    }

    UpdateResult MongoModel::update(int64_t id, const bsoncxx::builder::stream::document &document)
    {
        auto collection = this->getCollection();
        bsoncxx::builder::stream::document filter;
        filter << "id" << id;
        return collection.update_one(filter.view(), document.view());
    }

    DeleteResult MongoModel::deleteOne(int64_t id)
    {
        auto collection = this->getCollection();
        bsoncxx::builder::stream::document filter;
        filter << "id" << id;
        return collection.delete_one(filter.view());
    }

    DeleteResult MongoModel::deleteMany(const bsoncxx::builder::stream::document &filter)
    {
        auto collection = this->getCollection();
        return collection.delete_many(filter.view());
    }

    FindOneResult MongoModel::findOne(int64_t id)
    {
        auto collection = this->getCollection();
        bsoncxx::builder::stream::document filter;
        filter << "id" << id;
        return collection.find_one(filter.view());
    }

    FindResult MongoModel::find(const bsoncxx::builder::stream::document &filter)
    {
        auto collection = this->getCollection();
        return collection.find(filter.view());
    }

    void MongoModel::customOperator(const Function<void(mongocxx::collection &)> &func)
    {
        auto collection = this->getCollection();
        func(collection);
    }

    int64_t MongoModel::countDocuments(const bsoncxx::builder::stream::document &filter)
    {
        auto collection = this->getCollection();
        return collection.count_documents(filter.view());
    }

    auto MongoModel::batchInsert(const Vector<bsoncxx::builder::stream::document> &list)
    {
        auto collection = this->getCollection();
        return collection.insert_many(list.begin(), list.end());
    }

    bsoncxx::builder::stream::document Model::getModelDocument() const
    {
        bsoncxx::builder::stream::document document;
        document << "id" << id
                 << "created_at" << Model::convertStringToBdate(createdAt)
                 << "updated_at" << Model::convertStringToBdate(updatedAt);
        return document;
    }

    bsoncxx::types::b_date Model::convertStringToBdate(const String &date)
    {
        std::tm tm = {};
        std::istringstream ss(date);
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
        if (ss.fail())
        {
            throw std::runtime_error("Failed to parse date string.");
        }
        std::time_t time = std::mktime(&tm);
        if (time == -1)
        {
            throw std::runtime_error("Failed to convert time.");
        }
        auto milliseconds_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::from_time_t(time).time_since_epoch()
        ).count();
        return bsoncxx::types::b_date(std::chrono::milliseconds(milliseconds_since_epoch));
    }
}