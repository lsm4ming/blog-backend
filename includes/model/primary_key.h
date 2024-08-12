#ifndef BLOG_BACKEND_PRIMARY_KEY_H
#define BLOG_BACKEND_PRIMARY_KEY_H

#include "models.h"

namespace blog_backend::model
{
    using namespace cpptools::common;

    class PrimaryKey : public Model
    {
    public:
        String tableName;
        int64_t lastId{};

        [[nodiscard]] bsoncxx::builder::stream::document toDocument() const override;
    };

    class PrimaryKeyModel : public MongoModel
    {
    private:
        explicit PrimaryKeyModel() = default;

    public:
        PrimaryKeyModel(const PrimaryKeyModel &) = delete;

        PrimaryKeyModel &operator=(const PrimaryKeyModel &) = delete;

    public:
        ~PrimaryKeyModel() override = default;

        int64_t generateId(const String &tableName);

        String tableName() override;

        static PrimaryKeyModel *getInstance()
        {
            static PrimaryKeyModel primaryKeyModel{};
            return &primaryKeyModel;
        }
    };
}

#endif //BLOG_BACKEND_PRIMARY_KEY_H
