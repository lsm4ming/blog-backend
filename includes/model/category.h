#ifndef BLOG_BACKEND_CATEGORY_H
#define BLOG_BACKEND_CATEGORY_H

#include <string>

namespace blog_backend::model
{
    class Category
    {
    public:
        long id;
        std::string name;
    };
}

#endif //BLOG_BACKEND_CATEGORY_H
