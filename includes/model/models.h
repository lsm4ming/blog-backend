#ifndef BLOG_BACKEND_MODELS_H
#define BLOG_BACKEND_MODELS_H

#include <cpptools/common/singleton.h>
#include "common.h"
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
}

#endif //BLOG_BACKEND_MODELS_H
