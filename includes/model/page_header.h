//
// Created by Administrator on 2024-08-11.
//

#ifndef BLOG_BACKEND_PAGE_HEADER_H
#define BLOG_BACKEND_PAGE_HEADER_H

#include "common.h"

namespace blog_backend::model
{
    class PageHeader : public Model
    {
    public:
        String routeName;
        String bgUrl;
    };

    class PageHeaderModel : public MongoModel
    {
    public:
        String tableName() override;
    };
}


#endif //BLOG_BACKEND_PAGE_HEADER_H
