#include <iostream>
#include <cpptools/common/flag.h>
#include <cpptools/common/config.h>
#include <cpptools/http/httpserver.h>
#include <cpptools/log/log.h>
#include "config/config.h"
#include "controller/route.h"
#include "model/common.h"
#include "cache/redis.h"

constexpr const char *DEFAULT_CONFIG_PATH = "config/config.ini";

using namespace cpptools::http;
using namespace cpptools::common;
using namespace cpptools::log;

void usage()
{
    std::cout << "Usage: -c [config path]" << std::endl;
}

int main(int argc, char *argv[])
{
    // cpptools::log::LOG_LEVEL(cpptools::log::DEBUG);
    String cfgPath;
    SetUsage(usage);
    StrOpt(&cfgPath, "c", DEFAULT_CONFIG_PATH);
    Parse(argc, argv);

    IniConfig config;
    if (!config.load(cfgPath))
    {
        LOG_ERROR("load config failed, cfgPath: %s", cfgPath.c_str());
        throw std::runtime_error("load config failed");
    }
    blog_backend::config::setConfig(config);
    if (!blog_backend::config::checkConfig())
    {
        throw std::runtime_error("config check failed");
    }
    auto &c = blog_backend::config::getConfig();
    HttpServer server(c.server.host, c.server.port);
    blog_backend::controller::init(server);
    blog_backend::model::initMongodb(c);
    blog_backend::cache::initRedis(c);
    server.start();
    return 0;
}