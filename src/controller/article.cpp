#include "controller/article.h"

namespace blog_backend::controller
{
    template<typename T>
    void checkPageParam(T &page, T &size)
    {
        if (page <= 0)
        {
            page = 1;
        }
        if (size <= 0)
        {
            size = 10;
        }
        if (size > 100)
        {
            size = 100;
        }
    }

    void getArticleList(cpptools::http::Request &request, cpptools::http::HttpResponseWriter &response)
    {
        long size = std::strtol(request.getParam("size").c_str(), nullptr, 10);
        long page = std::strtol(request.getParam("page").c_str(), nullptr, 10);
        checkPageParam(page, size);
        auto articleModel = blog_backend::model::ArticleModel::getInstance();

        auto options = mongocxx::options::find{};

        // 排序条件
        bsoncxx::builder::stream::document sort{};
        sort << "id" << -1;
        options.sort(sort.view());

        // 分页条件
        options.skip((size - 1) * page);
        options.limit(size);

        auto cursor = articleModel->find({}, options);

        auto data = cpptools::json::JsonArray();
        for (auto &doc: cursor.value())
        {
            auto temp = cpptools::json::JsonValue();
            for (auto &field: std::array<String, 3>{
                    "article_title",
                    "article_description",
                    "article_cover"
            })
            {
                if (!doc[field])
                {
                    continue;
                }
                temp[field] = String(doc[field].get_string().value);
            }
            for (auto &field: std::array<String, 5>{
                    "author_id",
                    "category_id",
                    "view_times",
                    "thumbs_up_times",
                    "reading_duration"
            })
            {
                if (!doc[field])
                {
                    continue;
                }
                temp[field] = (int) doc[field].get_int64().value;
            }
            for (auto &field: std::array<String, 4>{
                    "order",
                    "type",
                    "is_top",
                    "status",
            })
            {
                if (!doc[field])
                {
                    continue;
                }
                temp[field] = (int) doc[field].get_int32().value;
            }
            for (auto &field: std::array<String, 2>{
                    "is_top",
                    "status",
            })
            {
                if (!doc[field])
                {
                    continue;
                }
                temp[field] = (int) doc[field].get_int32().value;
            }
            if (doc["tag_name_list"])
            {
                auto array = doc["tag_name_list"].get_array().value;
                auto tags = cpptools::json::JsonArray();
                for (auto &tag: array)
                {
                    tags.push_back(String(tag.get_string().value));
                }
                temp["tag_name_list"] = std::make_shared<cpptools::json::JsonArray>(tags);
            }
            data.push_back(std::make_shared<cpptools::json::JsonValue>(temp));
        }
        response.setContentType("application/json");
        auto result = cpptools::json::JsonValue();
        result["code"] = 200;
        result["msg"] = "查询成功";
        result["data"] = std::make_shared<cpptools::json::JsonArray>(data);
        response.write(result.toString());
    }
}