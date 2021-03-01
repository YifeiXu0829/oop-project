#pragma once


// base class of all roles
#include <memory>
#include <iostream>
#include "roles.h"

// add new requests here
enum class option : int32_t
{
    non_opt = 0,
    list_all_courses,
    register_course,
    TA_special_permission
};

// add new requests here
option get_opt(std::string_view v)
{
    if (v == "list_all_courses") return option::list_all_courses;
    if (v == "register_course") return option::register_course;
    if (v == "TA_special_permission") return option::TA_special_permission;
    return option::non_opt;
}

class controller;
class user
{
public:
    user(controller& c):ctr_(c)
    {

    }

    virtual ~user(){}

    // list base role's permissions
    void show_permissions() const
    {
        std::cout<<"You have the following Permissions:\n";
        std::cout<<"list_all_courses";
        this->show_other_permissions();
        std::cout<<"=========================================\n";
    }

    void process_request(std::string_view req)
    { 
        auto opt = get_opt(req);
 
        switch(opt)
        { 
            case option::list_all_courses:
                this->list_all_courses();
                break;
            default:
                this->process_derived_request(opt, req);
                break;
        } 
    }

protected:
    // derived should override this to add more permissions
    virtual void show_other_permissions() const
    {
    }

    virtual void list_all_courses()
    {
        std::cout<<"user request list_all_courses\n";
    }

    // derived class should override this to add their specific requesta
    virtual void process_derived_request(option opt, std::string_view v)
    {
        //std::cout<<"user unhandled request "<<v<<std::endl;
    }

private:
    controller& ctr_;
};

struct student : public virtual user
{
    student(controller& c):user(c)
    {

    }
    virtual ~student(){}

    void show_other_permissions() const override
    {
        user::show_other_permissions();
        std::cout<<"register_course\n";
    }

    virtual void list_all_courses() override
    {
        std::cout<<"student request list_all_courses\n";
    }

    virtual void register_course()
    {
        std::cout<<"request register_course\n";
    }

    virtual void process_derived_request(option opt, std::string_view v) override
    {
        user::process_derived_request(opt, v);
        switch(opt)
        {
               case option::register_course:
                   this->register_course();
                   break;
               default:
                   break;
        }
    }
};

struct faculty : public virtual user
{
    faculty(controller& c):user(c)
    {

    }
    virtual ~faculty(){}

    void show_other_permissions() const override
    {
        user::show_other_permissions();
        std::cout<<"\n";
    }

    virtual void grade_course()
    {
        std::cout<<"request grade_course\n";
    }
};

struct instructor : public virtual faculty
{
    instructor(controller& c): user(c), faculty(c)
    {

    }
    virtual ~instructor(){}
};

struct TA final : public instructor, student
{
    TA(controller& c):user(c), faculty(c), instructor(c), student(c)
    {

    }
    void show_other_permissions() const override
    {
          instructor::show_other_permissions();
          student::show_other_permissions();
          std::cout<<"TA_special_permission\n";
    }

    virtual void TA_special_permission()
    {
         std::cout<<"request TA_special_permission\n";
    }

    virtual void process_derived_request(option opt, std::string_view v) override
    {
        student::process_derived_request(opt, v);
        instructor::process_derived_request(opt, v);
        switch(opt)
        {
               case option::TA_special_permission:
                   this->TA_special_permission();
                   break;
               default:
                   break;
        }
    }
};

struct admin final : public faculty
{
    admin(controller& c): user(c), faculty(c)
    {

    }
};

class role_factory
{
public:
    static std::unique_ptr<user> make_role(role r, controller& c)
    {
        switch(r)
        {
            case role::admin:
                return std::make_unique<admin>(c);
            case role::student:
                return std::make_unique<student>(c);
            case role::TA:
                return std::make_unique<TA>(c);
            case role::faculty:
                return std::make_unique<faculty>(c);
            case role::instructor:
                return std::make_unique<instructor>(c);
            default:
                return nullptr;
        }
    }
};
