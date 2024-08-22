#ifndef BLOG_BACKEND_CONFIG_VIEW_H
#define BLOG_BACKEND_CONFIG_VIEW_H

#include <cpptools/http/server_request.h>
#include <cpptools/http/response_writer.h>
#include <cpptools/json/jsonparse.h>
#include "model/statistic.h"
#include "model/page_header.h"
#include "model/config.h"

namespace blog_backend::controller
{
    extern void addView(cpptools::http::Request &request, cpptools::http::HttpResponseWriter &response);

    extern void queryStatistic(cpptools::http::Request &request, cpptools::http::HttpResponseWriter &response);

    extern void queryPageHeader(cpptools::http::Request &request, cpptools::http::HttpResponseWriter &response);

    extern void queryBaseConfig(cpptools::http::Request &request, cpptools::http::HttpResponseWriter &response);
}

#endif //BLOG_BACKEND_CONFIG_VIEW_H
