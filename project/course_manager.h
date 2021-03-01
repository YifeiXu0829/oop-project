#pragma once

#include <iostream>
#include <string>
#include "roles.h"

// Interface segregation principle

using namespace std;

class controller;
class CourseManagerBase
{
public:
    CourseManagerBase(controller& c):ctr_(c){}
    virtual ~CourseManagerBase(){}

    void list_all_courses();
protected:
    controller& ctr_;
};

class StudentCourseManager : public CourseManagerBase
{
public:
    StudentCourseManager(controller& c):CourseManagerBase(c){}
    virtual ~StudentCourseManager(){}

    virtual void register_course(){cout<<"register_course\n";}
    virtual void drop_course(){}
    virtual void swap_course(){}
    virtual void get_my_grade(){}
};

class FacultyCourseManager : public CourseManagerBase
{
public:
    FacultyCourseManager(controller& c):CourseManagerBase(c){}
    virtual ~FacultyCourseManager(){}

    virtual void approve_registry(){}
    virtual void deny_registry(){}
    virtual void grade_course(){}
};

class InstructorCourseManager : public FacultyCourseManager
{
public:
    InstructorCourseManager(controller& c): FacultyCourseManager(c){}
    virtual ~InstructorCourseManager(){}

    virtual void add_course(){}
    virtual void modify_course(){}
    virtual void delete_course(){}
};

class AdminCourseManager : public CourseManagerBase
{
public:
    AdminCourseManager(controller& c): CourseManagerBase(c){}
    virtual ~AdminCourseManager(){}

    virtual void add_user(){}
    virtual void modify_user(){}
    virtual void delete_user(){};
};

class course_manager_factory
{
public:
    static std::unique_ptr<CourseManagerBase> make_course_manager(role r, controller& c)
    {
        switch(r)
        {
            case role::admin:
                return std::make_unique<AdminCourseManager>(c);
            case role::TA:
                [[fallthrough]];
            case role::student:
                return std::make_unique<StudentCourseManager>(c);
            case role::instructor:
                return std::make_unique<InstructorCourseManager>(c);
            case role::faculty:
                return std::make_unique<FacultyCourseManager>(c);
        }
    }
};
