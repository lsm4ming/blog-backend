#ifndef BLOG_BACKEND_PRIMARY_KEY_H
#define BLOG_BACKEND_PRIMARY_KEY_H

#include "common.h"

namespace blog_backend::model
{
    class PrimaryKey : public Model
    {
    public:
        String tableName;
        int64_t lastId{};

        [[nodiscard]] bsoncxx::builder::stream::document toDocument() const override;
    };

    class PrimaryKeyModel : public MongoModel
    {
    public:
        ~PrimaryKeyModel() override = default;

        int64_t generateId(const String &tableName);

        String tableName() override;
    };
}

#endif //BLOG_BACKEND_PRIMARY_KEY_H
