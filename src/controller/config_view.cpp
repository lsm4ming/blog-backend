#include "controller/config_view.h"
#include "model/defined.h"

namespace blog_backend::controller
{
    void addView(cpptools::http::Request &request, cpptools::http::HttpResponseWriter &response)
    {
        // 访问量visit_count++
        blog_backend::model::Statistic statistic;
        statistic.id = statistic.visitCount = 1;
        auto statisticModel = blog_backend::model::getStatisticModel();
        statisticModel.incrementStatistic(statistic);

        response.setContentType("application/json");
        response.write(
                "{"
                "\"code\": 200,"
                "\"msg\": \"Hello World!\""
                "}");
    }
}