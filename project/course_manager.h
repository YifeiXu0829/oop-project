#pragma once

#include <iostream>
#include <string>
#include "roles.h"

// Interface segregation principle

using namespace std;

class controller;
class course_manager
{
public:
    course_manager(controller& c) : ctrl_(c){}

    void list_all_courses()
    {
        db_conn_.list_all_courses();
    }
    bool find_course(std::string name)
    {
        return db_conn_.find_course(name);
    }
    bool add_course(std::string n, int cap, std::string instructor)
    {
        return db_conn_.add_course(n, cap, instructor);
    }
    bool modify_course(std::string n, int cap, std::string instructor)
    {
        return this->delete_course(n) && this->add_course(n, cap, instructor);
    }
    bool delete_course(std::string course_name)
    {
        return db_conn_.delete_course(course_name);
    }

private:
    course_tables_access db_conn_;
    controller& ctrl_;
};

