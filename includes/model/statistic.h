#ifndef BLOG_BACKEND_STATISTIC_H
#define BLOG_BACKEND_STATISTIC_H

#include "common.h"

namespace blog_backend::model
{
    class Statistic
    {
    public:
        long id;
        std::string name;
    };
}

#endif //BLOG_BACKEND_STATISTIC_H
