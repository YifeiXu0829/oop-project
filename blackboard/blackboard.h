#pragma once

#include <iostream>
#include "controller.h"

struct solution_space{};
struct central_data{};

class blackboard
{
public:

    template <class Input_Ty>
    void take_input(Input_Ty input)
    {
        std::cout<<"Blackboard takes input from external and notify controller\n";
        ctrl_.dispatch(input);
    }

    void update_solution_space(){}


    controller ctrl_{*this};

    central_data central_data_;
    solution_space solution_space_;
};
