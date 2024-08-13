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
        result["code"] = 200;
        result["msg"] = "操作成功";
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
            result["msg"] = "查询失败";
            response.write(result.toString());
            return;
        }
        // mongo bson转结构体
        auto doc = value->view();
        result["code"] = 200;
        result["msg"] = "查询成功";
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
        result["data"] = data;
        response.write(result.toString());
    }

    void queryPageHeader(cpptools::http::Request &request, cpptools::http::HttpResponseWriter &response)
    {
        auto pageHeaderModel = blog_backend::model::PageHeaderModel::getInstance();
        auto cursor = pageHeaderModel->find({});
        auto result = cpptools::json::JsonArray();
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
            result.push_back(std::make_shared<cpptools::json::JsonValue>(temp));
        }
        response.setContentType("application/json");
        response.write(result.toString());
    }
}