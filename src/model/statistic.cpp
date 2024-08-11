#include "model/statistic.h"

namespace blog_backend::model
{
    bsoncxx::builder::stream::document Statistic::toDocument() const
    {
        auto document = this->getModelDocument();
        document << "article_count" << articleCount
                 << "comment_count" << commentCount
                 << "category_count" << categoryCount
                 << "tag_count" << tagCount
                 << "visit_count" << visitCount;
        return document;
    }

    String StatisticModel::tableName()
    {
        return "statistic";
    }

    auto StatisticModel::incrementStatistic(const Statistic &statistic)
    {
        auto collection = this->getCollection();
        using bsoncxx::builder::stream::document;
        using bsoncxx::builder::stream::finalize;
        auto filter = document{} <<
                                 "id" << statistic.id
                                 << finalize;
        auto update = document{};
        update << "$inc" << bsoncxx::builder::stream::open_document;
        if (statistic.articleCount > 0)
        {
            update << "article_count" << statistic.articleCount;
        }
        if (statistic.categoryCount > 0)
        {
            update << "category_count" << statistic.categoryCount;
        }
        if (statistic.tagCount > 0)
        {
            update << "tag_count" << statistic.tagCount;
        }
        if (statistic.visitCount > 0)
        {
            update << "visit_count" << statistic.visitCount;
        }
        if (statistic.commentCount > 0)
        {
            update << "comment_count" << statistic.commentCount;
        }
        update << bsoncxx::builder::stream::close_document;
        mongocxx::options::find_one_and_update update_opts;
        update_opts.return_document(mongocxx::options::return_document::k_after);
        update_opts.upsert(true);
        return collection.find_one_and_update(filter.view(), update.view(), update_opts);
    }
}