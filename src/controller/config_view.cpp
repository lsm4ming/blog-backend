#include "controller/config_view.h"

namespace blog_backend::controller
{
    void addView(cpptools::http::Request &request, cpptools::http::HttpResponseWriter &response)
    {
        // 访问量visit_count++
        blog_backend::model::Statistic statistic;
        statistic.id = statistic.visitCount = 1;
        auto statisticModel = blog_backend::model::StatisticModel::getInstance();
        statisticModel->incrementStatistic(statistic);
        response.setContentType("application/json");
        auto result = cpptools::json::JsonValue();
        result["code"] = 0;
        result["message"] = "操作成功";
        response.write(result.toString());
    }

    void queryStatistic(cpptools::http::Request &request, cpptools::http::HttpResponseWriter &response)
    {
        auto statisticModel = blog_backend::model::StatisticModel::getInstance();
        auto value = statisticModel->findOne(1);
        auto result = cpptools::json::JsonValue();
        response.setContentType("application/json");
        if (!value)
        {
            result["code"] = 400;
            result["message"] = "查询失败";
            response.write(result.toString());
            return;
        }
        // mongo bson转结构体
        auto doc = value->view();
        result["code"] = 0;
        result["message"] = "查询成功";
        auto data = cpptools::json::JsonValue();
        for (auto &field: std::array<String, 5>{
                "visit_count",
                "tag_count",
                "comment_count",
                "category_count",
                "article_count"
        })
        {
            if (!doc[field])
            {
                continue;
            }
            data[field] = (int) doc[field].get_int64().value;
        }
        result["result"] = data;
        response.write(result.toString());
    }

    void queryPageHeader(cpptools::http::Request &request, cpptools::http::HttpResponseWriter &response)
    {
        auto pageHeaderModel = blog_backend::model::PageHeaderModel::getInstance();
        auto cursor = pageHeaderModel->find({});
        auto data = cpptools::json::JsonArray();
        for (auto &doc: cursor.value())
        {
            auto temp = cpptools::json::JsonValue();
            for (auto &field: std::array<String, 2>{
                    "route_name",
                    "bg_url"
            })
            {
                if (!doc[field])
                {
                    continue;
                }
                temp[field] = String(doc[field].get_string().value);
            }
            temp["id"] = (int) doc["id"].get_int64().value;
            data.push_back(temp);
        }
        response.setContentType("application/json");
        auto result = cpptools::json::JsonValue();
        result["code"] = 0;
        result["message"] = "查询成功";
        result["result"] = std::make_shared<cpptools::json::JsonArray>(data);
        response.write(result.toString());
    }

    void queryBaseConfig(cpptools::http::Request &request, cpptools::http::HttpResponseWriter &response)
    {
        auto baseConfigModel = blog_backend::model::BaseConfigModel::getInstance();

        auto record = baseConfigModel->findOne(1);
        auto result = cpptools::json::JsonValue();
        response.setContentType("application/json");
        if (record)
        {
            auto doc = record->view();
            auto stringField = {
                    "blog_name",
                    "blog_avatar",
                    "avatar_bg",
                    "personal_say",
                    "blog_notice",
                    "qq_link",
                    "we_chat_link",
                    "github_link",
                    "gitee_link",
                    "bilibili_link",
                    "we_chat_group",
                    "qq_group",
                    "we_chat_pay",
                    "ali_pay",
                    "git_ee_link",
            };
            auto config = cpptools::json::JsonValue();
            for (auto &key: stringField)
            {
                if (!doc[key])
                {
                    continue;
                }
                config[key] = String(doc[key].get_string().value);
            }
            config["view_time"] = doc["view_time"].get_int32().value;
            config["id"] = (int) doc["id"].get_int64().value;
            config["createdAt"] = "";
            config["updatedAt"] = "";
            result["result"] = config;
        }
        result["code"] = 0;
        result["message"] = "查询成功";
        response.write(result.toString());
    }
}