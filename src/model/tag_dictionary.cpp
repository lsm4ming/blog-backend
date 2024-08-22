#include "model/tag_dictionary.h"

namespace blog_backend::model
{
    bsoncxx::builder::stream::document TagDictionary::toDocument() const
    {
        auto document = this->getModelDocument();
        document << "tag_name" << this->tagName
                 << "id" << this->id;
        return document;
    }
}


