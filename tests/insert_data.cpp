#include <iostream>
#include <cpptools/common/flag.h>
#include <cpptools/common/config.h>
#include <cpptools/time/time.h>
#include "model/page_header.h"
#include "model/primary_key.h"
#include "model/config.h"

constexpr const char *DEFAULT_CONFIG_PATH = "config/config.ini";

using namespace cpptools::common;

void usage()
{
    std::cout << "Usage: -c [config path]" << std::endl;
}

void insertPageHeader()
{
    auto dataMap = HashMap<String, String>{
            std::pair<String, String>("Archives", "http://img.mrzym.top/FlFlA2XjKkwPD4lRlFwxZc4mUsLt"),
            std::pair<String, String>("Front", "http://img.mrzym.top/FspmnaMX03SBQnSSOrc89AYU6WD6"),
            std::pair<String, String>("Back", "http://img.mrzym.top/Fuu4w1ZRXo4qteomv0iInTWaZJnV"),
            std::pair<String, String>("SiteList", "http://img.mrzym.top/Fk7tZJknslpjfuWYJ7t7WBRp1fko"),
            std::pair<String, String>("Category", "http://img.mrzym.top/Fjiasg7yStHBnRk2kjz1xknjF3iJ"),
            std::pair<String, String>("Tag", "http://img.mrzym.top/FglVTbjobxaerUyYjxcr8aSbe--G"),
            std::pair<String, String>("PhotoAlbum", "http://img.mrzym.top/FhVJ8zBgi7pNy33yhQh9Lh05wOr5"),
            std::pair<String, String>("Photos", "http://img.mrzym.top/Fj9jQJlzi5AjYhdTtdhbSF_5RPcZ"),
            std::pair<String, String>("Talk", "http://img.mrzym.top/Fh1XXJSJ3dKKp65VDQaEhW4JVV66"),
            std::pair<String, String>("UserCenter", "http://img.mrzym.top/FkmggZhOwM_6eq-_vX6P8iSiWctb"),
            std::pair<String, String>("LinkList", "http://img.mrzym.top/FiCIpxwaz2M5GwNrq7U0r3OQ2eaT"),
            std::pair<String, String>("ArticleList", "http://img.mrzym.top/FsNNILnTcg_VzzEXbZQl-qLnFNje"),
            std::pair<String, String>("Home", "http://img.mrzym.top/FvqmN1uzeffmGusWK8DvZj8IGaTi"),
    };

    auto pageModel = blog_backend::model::PageHeaderModel::getInstance();
    auto pkModel = blog_backend::model::PrimaryKeyModel::getInstance();
    for (auto &[k, v]: dataMap)
    {
        auto record = blog_backend::model::PageHeader();
        String now = cpptools::time::Time::now().format("%Y-%m-%d %H:%M:%S");
        record.id = pkModel->generateId(pageModel->tableName());
        record.bgUrl = v;
        record.routeName = k;
        record.createdAt = now;
        record.updatedAt = now;
        pageModel->insert(record);
    }
}

void insertBaseConfig()
{
    auto pkModel = blog_backend::model::PrimaryKeyModel::getInstance();
    auto baseConfigModel = blog_backend::model::BaseConfigModel::getInstance();
    blog_backend::model::BaseConfig config;
    String now = cpptools::time::Time::now().format("%Y-%m-%d %H:%M:%S");
    config.id = pkModel->generateId(baseConfigModel->tableName());
    config.createdAt = now;
    config.updatedAt = now;
    config.aliPay = "";
    config.avatarBg = "";
    config.qqLink = "https://cdn.lsm1998.com/blog/3f589106152f484f8faa44decd1a2077.jpg";
    config.weChatLink = "https://cdn.lsm1998.com/blog/02fbed77ae714a0797a8d3b65ef05c6f.jpg";
    config.blogAvatar = "";
    config.gitEeLink = "https://gitee.com/lsm1998_admin";
    config.githubLink = "https://github.com/lsm1998";
    config.personalSay = "为什么每天不能睡25个小时啊。";
    config.blogNotice ="博客公告";
    config.blogName = "lsm1998的博客";
    config.viewTime = 0;
    config.weChatGroup = "";
    config.qqGroup = "";
    config.weChatPay = "";
    baseConfigModel->insert(config);
}

int main(int argc, char *argv[])
{
    String cfgPath;
    SetUsage(usage);
    StrOpt(&cfgPath, "c", DEFAULT_CONFIG_PATH);
    Parse(argc, argv);

    IniConfig config;
    if (!config.load(cfgPath))
    {
        throw std::runtime_error("load config failed");
    }
    blog_backend::config::setConfig(config);
    if (!blog_backend::config::checkConfig())
    {
        throw std::runtime_error("config check failed");
    }
    auto &c = blog_backend::config::getConfig();
    blog_backend::model::initMongodb(c);

    // insertBaseConfig();
    return 0;
}