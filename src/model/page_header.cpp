#include "model/page_header.h"

namespace blog_backend::model
{
    String PageHeaderModel::tableName()
    {
        return "page_header";
    }

    bsoncxx::builder::stream::document PageHeader::toDocument() const
    {
        auto document = this->getModelDocument();
        document << "bg_url" << this->bgUrl
                 << "route_name" << this->routeName;
        return document;
    }
}