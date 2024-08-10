#include "controller/http_handler.h"

namespace blog_backend::controller
{
    void ping(const cpptools::http::Request &request, cpptools::http::HttpResponseWriter &response)
    {
        response.setContentType("application/json");
        response.write(
                "{"
                "\"code\": 200,"
                "\"msg\": \"Hello World!\""
                "}");
    }

    void queryBlogCategory(const cpptools::http::Request &request, cpptools::http::HttpResponseWriter &response)
    {
    }
}