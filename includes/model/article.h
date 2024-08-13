#pragma once

#include "models.h"

namespace blog_backend::model
{
    using namespace cpptools::common;

    class Article : public Model
    {
    public:
        String articleTitle;
        int64_t authorId;
        int64_t categoryId;
        String articleDescription;
        String articleCover;
        int8_t isTop;
        int32_t order;
        int8_t status;
        int32_t type;
        int64_t viewTimes;
        int64_t thumbsUpTimes;
        int64_t readingDuration;
        Vector<String> tagNameList;
    };

    class ArticleModel : public MongoModel
    {
    private:
        ArticleModel() = default;

    public:
        ArticleModel(const ArticleModel &) = delete;

        ArticleModel &operator=(const ArticleModel &) = delete;

    public:
        String tableName() override;

        static ArticleModel *getInstance()
        {
            static ArticleModel articleModel{};
            return &articleModel;
        }
    };
}