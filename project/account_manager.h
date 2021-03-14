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
        //return {false, 'A'};
        //return {true, 'T')};
        return db_.validate_credential(usrname, password);
    }

    void get_my_grade(){std::cout<<"test get_my_grade\n";}
    virtual void register_course(string usrname, string course)
    {
        db_.register_course(usrname, course);
    }
    virtual void drop_course(string usrname, string course)
    {
        db_.drop_course(usrname, course);
    }

    virtual void approve_registry(){}
    virtual void deny_registry(){}
    virtual void grade_course(){std::cout<<"test grade_course\n";}

    virtual void add_user(std::string username, std::string pw, std::string role)
    {
        auto ok = db_.add_user(username, pw, role);
        if(ok)
        {
            std::cout<<"successfully added user:"<<username<<" role:"<<role<<std::endl;
        }
    }

    virtual void modify_user(std::string username, std::string pw, std::string role)
    {
        [[maybe_unused]] auto ok = db_.modify_user(username, pw, role);
    }

    virtual void delete_user(std::string username)
    {
        [[maybe_unused]] auto ok = db_.delete_user(username);
    }

private:
    controller& ctrl_;
	account_tables_access db_;
};
