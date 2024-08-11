#include "model/common.h"

namespace blog_backend::model
{
    void initMongodb(blog_backend::config::Config &c)
    {
        mongocxx::uri uri{"mongodb://" + c.mongodb.username + ":" + c.mongodb.password + "@" + c.mongodb.host + ":" + std::to_string(c.mongodb.port)};
        mongocxx::client client(uri);
        mongocxx::database db = client["blog"];
    }
}