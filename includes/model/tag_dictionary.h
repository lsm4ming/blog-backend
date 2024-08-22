#pragma once

#include "models.h"

namespace blog_backend::model
{
    using namespace cpptools::common;

    class TagDictionary : public Model
    {
    public:
        String tagName;

        [[nodiscard]] bsoncxx::builder::stream::document toDocument() const override;
    };

    class TagDictionaryModel : public MongoModel
    {
    public:
        String tableName() override
        {
            return "tag_dictionary";
        }

        static TagDictionaryModel *getInstance()
        {
            static TagDictionaryModel tagDictionaryModel{};
            return &tagDictionaryModel;
        }
    };
}