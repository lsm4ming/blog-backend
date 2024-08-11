#include "controller/config.h"

namespace blog_backend::controller
{
    void addView(const cpptools::http::Request &request, cpptools::http::HttpResponseWriter &response)
    {
        response.setContentType("application/json");
        response.write(
                "{"
                "\"code\": 200,"
                "\"msg\": \"Hello World!\""
                "}");
    }
}