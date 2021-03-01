#pragma once

#include "Interfaces.h"

class Instructor final: public InstructorInterface
{
public:
    using base = InstructorInterface;
    void teach_class()
    {
        base::get_enrollment_numbers();
        base::get_classroom();
        base::enter_grades();
    }

    void log() override
    {
        logger_.log("Instructor logging ...");
    }
};
