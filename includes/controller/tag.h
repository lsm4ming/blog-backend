#pragma once

#include <cpptools/http/server_request.h>
#include <cpptools/http/response_writer.h>
#include <cpptools/json/jsonparse.h>
#include "model/tag_dictionary.h"

namespace blog_backend::controller
{
    extern void queryTagDictionary(cpptools::http::Request &request, cpptools::http::HttpResponseWriter &response);
}