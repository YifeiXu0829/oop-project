#pragma once

#include "Interfaces.h"

class Registrar final: public RegistrarInterface
{
public:
    using base = RegistrarInterface;
    void create_class()
    {
        base::add_class_to_quarter_schedule();
        base::set_instructor_for_class();
        base::get_enrollment_numbers();
        base::run_class();
    }

    void log() override
    {
        logger_.log("Registrar logging ...");
    }
};
