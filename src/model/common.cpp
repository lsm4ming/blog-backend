#include "model/common.h"

namespace blog_backend::model
{
    mongocxx::instance instance{};

    mongocxx::client globalClient{};

    void initMongodb(blog_backend::config::Config &c)
    {
        try
        {
            mongocxx::uri uri{
                    "mongodb://" + c.mongodb.username + ":" + c.mongodb.password + "@" + c.mongodb.host + ":" +
                    std::to_string(c.mongodb.port)};
            globalClient = mongocxx::client(uri);
            std::cout << "Connection MongoDB successful!" << std::endl;
        } catch (const mongocxx::exception &e)
        {
            std::cerr << "MongoDB error: " << e.what() << std::endl;
        }
    }


}