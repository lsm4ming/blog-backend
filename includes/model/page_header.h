#ifndef BLOG_BACKEND_PAGE_HEADER_H
#define BLOG_BACKEND_PAGE_HEADER_H

#include "models.h"

namespace blog_backend::model
{
    using namespace cpptools::common;

    class PageHeader : public Model
    {
    public:
        String routeName;
        String bgUrl;

        [[nodiscard]] bsoncxx::builder::stream::document toDocument() const override;
    };

    class PageHeaderModel : public MongoModel
    {
    private:
        explicit PageHeaderModel() = default;

    public:
        PageHeaderModel(const PageHeaderModel &) = delete;

        PageHeaderModel &operator=(const PageHeaderModel &) = delete;

    public:
        String tableName() override;

        static PageHeaderModel *getInstance()
        {
            static PageHeaderModel pageHeaderModel{};
            return &pageHeaderModel;
        }
    };
}

#endif //BLOG_BACKEND_PAGE_HEADER_H
