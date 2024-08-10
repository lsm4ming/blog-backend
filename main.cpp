#include <iostream>
#include <cpptools/http/httpserver.h>
#include "controller/http_handler.h"

constexpr const char *DEFAULT_HOST = "127.0.0.1";
constexpr const char *DEFAULT_PORT = "8080";

using namespace cpptools::http;

int main(int argc, char *argv[])
{
    std::vector<std::string> args(argv, argv + argc);
    if (argc < 3)
    {
        args.emplace_back(DEFAULT_HOST);
        args.emplace_back(DEFAULT_PORT);
    }
    HttpServer server(args[1], std::atoi(args[2].c_str()));
    server.addRoute(HttpMethod::HTTP_GET, "/ping", blog_backend::controller::ping);
    server.addRoute(HttpMethod::HTTP_GET, "/category", blog_backend::controller::queryBlogCategory);
    server.addRoute(HttpMethod::HTTP_POST, "/category", blog_backend::controller::queryBlogCategory);
    server.start();
    return 0;
}