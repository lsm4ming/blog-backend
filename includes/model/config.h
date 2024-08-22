#pragma once

#include "models.h"

namespace blog_backend::model
{
    using namespace cpptools::common;

    class BaseConfig : public Model
    {
    public:
        // 博客名称
        String blogName;
        // 博客图片
        String blogAvatar;
        // 博客背景图片
        String avatarBg;
        // 个人介绍
        String personalSay;
        // 博客公告
        String blogNotice;
        // qq 链接
        String qqLink;
        // weChat 链接
        String weChatLink;
        // github 链接
        String githubLink;
        // gitee 链接
        String gitEeLink;
        // bilibili 链接
        String bilibiliLink;
        // 访问量
        int32_t viewTime{};
        // 微信群链接
        String weChatGroup;
        // qq 群链接
        String qqGroup;
        // 微信支付
        String weChatPay;
        // 支付宝
        String aliPay;

        [[nodiscard]] bsoncxx::builder::stream::document toDocument() const override;
    };

    class BaseConfigModel : public MongoModel
    {
    private:
        BaseConfigModel() = default;

    public:
        BaseConfigModel(const BaseConfigModel &) = delete;

        BaseConfigModel &operator=(const BaseConfigModel &) = delete;

    public:
        String tableName() override;

        static BaseConfigModel *getInstance()
        {
            static BaseConfigModel baseConfigModel{};
            return &baseConfigModel;
        }
    };
}