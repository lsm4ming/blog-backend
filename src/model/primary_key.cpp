#include "model/primary_key.h"

namespace blog_backend::model
{
    String PrimaryKeyModel::tableName()
    {
        return "primary_key";
    }

    int64_t PrimaryKeyModel::generateId(const String &tableName)
    {
        auto collection = this->getCollection();

        using bsoncxx::builder::stream::document;
        using bsoncxx::builder::stream::finalize;

        auto filter = document{} <<
                                 "table_name" << tableName
                                 << finalize;
        auto update = document{}
                << "$inc" << bsoncxx::builder::stream::open_document
                << "last_id" << static_cast<int64_t>(1)
                << bsoncxx::builder::stream::close_document
                << finalize;

        // find_one_and_update
        mongocxx::options::find_one_and_update update_opts;
        update_opts.return_document(mongocxx::options::return_document::k_after);
        update_opts.upsert(true);

        auto result = collection.find_one_and_update(filter.view(), update.view(), update_opts);
        if (!result)
        {
            throw std::runtime_error("No document found or error in update operation.");
        }
        bsoncxx::document::view view = result->view();
        return view["last_id"].get_int64().value;
    }

    bsoncxx::builder::stream::document PrimaryKey::toDocument() const
    {
        auto document = this->getModelDocument();
        document << "last_id" << this->lastId
                 << "table_name" << this->tableName;
        return document;
    }
}

