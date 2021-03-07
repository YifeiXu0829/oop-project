#pragma once

#include "user.h"
#include "account_manager.h"
#include "course_manager.h"

struct logger
{
    void log(std::string s)
    {
        std::cout<<s<<std::endl;
    }
};

class controller
{
public:
    using string = std::string;

    void login(string usrname, string password)
    {
        auto [ok, role_str] = account_manager_.validate_credential(usrname, password);
        if(!ok)
        {
            std::cout<<"wrong credentials, exit(1)\n";
            exit(1);
        }

        std::cout<<"welcome to REGIE system\n";

        user_ = role_factory::make_role(static_cast<role>(role_str), *this);
        user_->show_permissions();
    }

    void send_request(std::string_view req)
    {
        user_->process_request(req);
    }

    void log (std::string content)
    {
        logger_.log(content);
    }

private:
    account_manager account_manager_{*this};
    course_manager course_manager_{*this};
    std::unique_ptr<user> user_{nullptr};
    logger logger_;
};
