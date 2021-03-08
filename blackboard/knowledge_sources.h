#pragma once

#include <iostream>

class blackboard;
struct knowledge_source_string
{
    static void process_input_and_update_blackboard(blackboard& bb, std::string input)
    {
        std::cout<<"string knowledge source processed and update to blackboard solution space\n";
    }
};

struct knowledge_source_int
{
    static void process_input_and_update_blackboard(blackboard& bb, int32_t input)
    {
        std::cout<<"int32_t knowledge source processed and update to blackboard solution space\n";
    }
};

struct knowledge_source_double
{
    static void process_input_and_update_blackboard(blackboard& bb, double input)
    {
        std::cout<<"double knowledge source processed and update to blackboard solution space\n";
    }
};
