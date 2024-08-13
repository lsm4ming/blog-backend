#include "controller/route.h"

namespace blog_backend::controller
{
    void init(HttpServer &server)
    {
        server.addRoute(HttpMethod::HTTP_GET, "/ping", ping);
        server.addRoute(HttpMethod::HTTP_GET, "/category", queryBlogCategory);
        server.addRoute(HttpMethod::HTTP_POST, "/category", queryBlogCategory);

        // ---- config ----
        server.addRoute(HttpMethod::HTTP_PUT, "/api/config/addView", addView);
        server.addRoute(HttpMethod::HTTP_GET, "/api/statistic", queryStatistic);
        server.addRoute(HttpMethod::HTTP_GET, "/api/pageHeader/getAll", queryPageHeader);

        // ---- article ----
        server.addRoute(HttpMethod::HTTP_GET, "/api/article/blogHomeGetArticleList/:page/:size", getArticleList);
    }
}