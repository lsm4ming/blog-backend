#ifndef BLOG_BACKEND_DEFINED_H
#define BLOG_BACKEND_DEFINED_H

#include "primary_key.h"
#include "statistic.h"
#include "page_header.h"

namespace blog_backend::model
{
    static PrimaryKeyModel &getPrimaryKeyModel()
    {
        static PrimaryKeyModel primaryKeyModel;
        return primaryKeyModel;
    }

    static PageHeaderModel &getPageHeaderModel()
    {
        static PageHeaderModel pageHeaderModel;
        return pageHeaderModel;
    }
}

#endif //BLOG_BACKEND_DEFINED_H
