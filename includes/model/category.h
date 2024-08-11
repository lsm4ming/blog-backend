#ifndef BLOG_BACKEND_CATEGORY_H
#define BLOG_BACKEND_CATEGORY_H

#include "models.h"

namespace blog_backend::model
{
    using namespace cpptools::common;

    class Category
    {
    public:
        long id;
        String name;
    };
}

#endif //BLOG_BACKEND_CATEGORY_H
