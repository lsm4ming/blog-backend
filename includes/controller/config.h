#ifndef BLOG_BACKEND_CONFIG_H
#define BLOG_BACKEND_CONFIG_H

#include <cpptools/http/server_request.h>
#include <cpptools/http/response_writer.h>

namespace blog_backend::controller
{
    void addView(const cpptools::http::Request& request, cpptools::http::HttpResponseWriter& response);
}

#endif //BLOG_BACKEND_CONFIG_H
