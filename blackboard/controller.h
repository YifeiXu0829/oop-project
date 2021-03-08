#pragma once

#include <iostream>
#include <type_traits>
#include "knowledge_sources.h"

class blackboard;
struct controller
{
    explicit controller(blackboard& bb):bb_(bb){}

    template <class Input_Ty>
    void dispatch(Input_Ty input)
    {
        std::cout<<"controller receives state change from Blackboard and dispatch it to chosen knowledge source\n";

        if constexpr (std::is_same_v<decltype(input), std::string>)
        {
            knowledge_source_string::process_input_and_update_blackboard(bb_, input);
        }
        else if constexpr (std::is_same_v<decltype(input), int32_t>)
        {
            knowledge_source_int::process_input_and_update_blackboard(bb_, input);
        }
        else if constexpr (std::is_same_v<decltype(input), double>)
        {
            knowledge_source_double::process_input_and_update_blackboard(bb_, input);
        }
        else
        {
            std::cout<<"no avaiable knowledge source to handle it\n";
        }
    }

    blackboard& bb_;
};
