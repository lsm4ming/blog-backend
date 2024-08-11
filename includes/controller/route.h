#ifndef BLOG_BACKEND_ROUTE_H
#define BLOG_BACKEND_ROUTE_H

#include <cpptools/http/httpserver.h>
#include "http_handler.h"
#include "config.h"

using namespace cpptools::http;

namespace blog_backend::controller
{
    extern void init(HttpServer& server);
}

#endif //BLOG_BACKEND_ROUTE_H
