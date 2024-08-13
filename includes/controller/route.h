#pragma once

#include <cpptools/http/httpserver.h>
#include "http_handler.h"
#include "config_view.h"
#include "article.h"

using namespace cpptools::http;

namespace blog_backend::controller
{
    extern void init(HttpServer& server);
}
