#include "model/config.h"

namespace blog_backend::model
{
    String blog_backend::model::BaseConfigModel::tableName()
    {
        return "base_config";
    }

    bsoncxx::builder::stream::document BaseConfig::toDocument() const
    {
        auto document = this->getModelDocument();
        document << "blog_name" << this->blogName
                    << "blog_avatar" << this->blogAvatar
                    << "avatar_bg" << this->avatarBg
                    << "personal_say" << this->personalSay
                    << "blog_notice" << this->blogNotice
                    << "qq_link" << this->qqLink
                    << "we_chat_link" << this->weChatLink
                    << "github_link" << this->githubLink
                    << "git_ee_link" << this->gitEeLink
                    << "bilibili_link" << this->bilibiliLink
                    << "view_time" << this->viewTime
                    << "we_chat_group" << this->weChatGroup
                    << "qq_group" << this->qqGroup
                    << "we_chat_pay" << this->weChatPay
                    << "ali_pay" << this->aliPay;
        return document;
    }
}