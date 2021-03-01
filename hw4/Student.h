#pragma once

#include "Interfaces.h"

class Student final: public StudentInterface
{
public:
    using base = StudentInterface;
    void register_for_class() override
    {
        base::register_for_class();
        base::pay_tuition();
        base::get_classroom();
        base::get_my_grade();
    }

    void log() override
    {
        logger_.log("Student logging ...");
    }
};
