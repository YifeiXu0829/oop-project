#pragma once

#include <iostream>
#include "controller.h"

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
};
