#pragma once

#include <iostream>
#include <string>

// the porblem was RegistrarInterface has too many methods not related with Registrar
// solution is to create a base interface, which implementes 3 interfaces, which are 
// StudentInterface, RegistrarInterface and InstructorInterface. With each contains the 
// methods only intended for their only client - Student, Registrar and Instructor.

struct logger
{
    void log(std::string s)
    {
        std::cout<<s<<std::endl;
    }
};

class InterfaceBase
{
public:
    virtual void log()
    {
        logger_.log("interface base log");
    }

    virtual ~InterfaceBase(){}
protected:
    logger logger_;
};

class StudentInterface : public InterfaceBase
{
public:
    virtual ~StudentInterface(){}

    virtual void register_for_class(){}
    virtual void pay_tuition(){}
    virtual void get_classroom(){}
    virtual void get_my_grade(){}
};

class RegistrarInterface : public InterfaceBase
{
public:
    virtual ~RegistrarInterface(){}

    virtual void add_class_to_quarter_schedule(){}
    virtual void set_instructor_for_class(){}
    virtual void get_enrollment_numbers(){}
    virtual void run_class(){}
};

class InstructorInterface : public InterfaceBase
{
public:
    virtual ~InstructorInterface(){}

    virtual void get_enrollment_numbers(){}
    virtual void get_classroom(){}
    virtual void enter_grades(){}
};


