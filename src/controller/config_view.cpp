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
        // mongo bson转结构体
        if (!value)
        {
            result["code"] = 400;
            result["msg"] = "查询失败";
            response.write(result.toString());
            return;
        }
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
}