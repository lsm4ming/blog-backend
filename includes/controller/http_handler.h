#ifndef BLOG_BACKEND_HTTP_HANDLER_H
#define BLOG_BACKEND_HTTP_HANDLER_H

#include <cpptools/http/server_request.h>
#include <cpptools/http/response_writer.h>

namespace blog_backend::controller
{
    extern void ping(const cpptools::http::Request& request, cpptools::http::HttpResponseWriter& response);

    extern void queryBlogCategory(const cpptools::http::Request& request, cpptools::http::HttpResponseWriter& response);
}

#endif //BLOG_BACKEND_HTTP_HANDLER_H
