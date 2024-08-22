#include "controller/tag.h"

namespace blog_backend::controller
{
    void queryTagDictionary(cpptools::http::Request &request, cpptools::http::HttpResponseWriter &response)
    {
        auto tagDictionaryModel = model::TagDictionaryModel::getInstance();
        auto cursor = tagDictionaryModel->find({});
        response.setContentType("application/json");
        auto result = cpptools::json::JsonValue();
        auto data = cpptools::json::JsonArray();
        for (auto &doc: cursor.value())
        {
            auto temp = cpptools::json::JsonValue();
            temp["id"] = (int) doc["id"].get_int64().value;
            temp["tag_name"] = doc["tag_name"].get_string().value.to_string();
            data.push_back(temp);
        }
        result["result"] = std::make_shared<cpptools::json::JsonArray>(data);
        result["message"] = "查询成功";
        result["code"] = 0;
        response.write(result.toString());
    }
}