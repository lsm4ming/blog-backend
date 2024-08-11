#ifndef BLOG_BACKEND_STATISTIC_H
#define BLOG_BACKEND_STATISTIC_H

#include "models.h"

namespace blog_backend::model
{
    using namespace cpptools::common;

    class Statistic : public Model
    {
    public:
        // 文章数量
        int64_t articleCount{};
        // 评论数量
        int64_t commentCount{};
        // 分类数量
        int64_t categoryCount{};
        // 标签数量
        int64_t tagCount{};
        // 访问数量
        int64_t visitCount{};

        /**
         * 转换为bson
         * @return
         */
        [[nodiscard]] bsoncxx::builder::stream::document toDocument() const override;
    };

    class StatisticModel : public MongoModel
    {
    public:
        /**
         * 增加统计数据
         * @param statistic
         * @return
         */
        FindOneResult incrementStatistic(const Statistic &statistic);

        String tableName() override;
    };
}

#endif //BLOG_BACKEND_STATISTIC_H
