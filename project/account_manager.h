#pragma once

#include <iostream>
#include <tuple>
#include <string>

#include "database_access.h"

class controller;

class account_manager
{
public:
    using string = std::string;
    
    account_manager(controller& c):ctrl_(c){}

    // get into postgresql database to validate credential and get role info
    std::tuple<bool, char> validate_credential(string usrname, string password)
    {
        //return std::make_tuple(false, "");
        //return std::make_tuple(true, 'T');
        return db_.validate_credential(usrname, password);
    }

    void get_my_grade(){}
    virtual void register_course(){std::cout<<"register_course\n";}
    virtual void drop_course(){}
    virtual void swap_course(){}

    virtual void approve_registry(){}
    virtual void deny_registry(){}
    virtual void grade_course(){}

    virtual void add_user(std::string username, std::string pw, std::string role)
    {
        auto ok = db_.add_user(username, pw, role);
        if(ok)
        {
            std::cout<<"successfully added user:"<<username<<" role:"<<role<<std::endl;
        }
    }
    virtual void modify_user(){}
    virtual void delete_user(){};

private:
    controller& ctrl_;
	account_tables_access db_;
};
