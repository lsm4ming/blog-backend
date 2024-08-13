#pragma once

#include <cpptools/http/server_request.h>
#include <cpptools/http/response_writer.h>
#include <cpptools/json/jsonparse.h>
#include "model/article.h"

namespace blog_backend::controller
{
    extern void getArticleList(cpptools::http::Request& request, cpptools::http::HttpResponseWriter& response);
}
