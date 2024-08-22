#include "controller/route.h"

namespace blog_backend::controller
{
    void options(cpptools::http::Request &request, cpptools::http::HttpResponseWriter &response)
    {
        response.setContentType("text/plain");
        response.setStatus(HttpStatus::HTTP_NO_CONTENT);
    }

    void init(HttpServer &server)
    {
        // ---- ping ----
        server.addRoute(HttpMethod::HTTP_GET, "/ping", ping);

        // ---- category ----
        server.addRoute(HttpMethod::HTTP_GET, "/category", queryBlogCategory);
        server.addRoute(HttpMethod::HTTP_POST, "/category", queryBlogCategory);

        // ---- config ----
        // server.addRoute(HttpMethod::HTTP_PUT, "/api/config", addView);
        server.addRoute(HttpMethod::HTTP_OPTIONS, "/api/config/addView", options);
        server.addRoute(HttpMethod::HTTP_PUT, "/api/config/addView", addView);
        server.addRoute(HttpMethod::HTTP_GET, "/api/statistic", queryStatistic);
        server.addRoute(HttpMethod::HTTP_GET, "/api/pageHeader/getAll", queryPageHeader);
        server.addRoute(HttpMethod::HTTP_GET, "/api/config", queryBaseConfig);

        // ---- article ----
        server.addRoute(HttpMethod::HTTP_GET, "/api/article/blogHomeGetArticleList/:page/:size", getArticleList);
    }
}