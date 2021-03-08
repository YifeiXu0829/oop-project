#include "blackboard.h"
#include <chrono>
#include <thread>

int main()
{
    blackboard bb;

    while (1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        std::string str_input = "string input";
        bb.take_input(str_input);

        std::cout<<"=========================================================\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        int32_t int_input = 0;
        bb.take_input(int_input);

        std::cout<<"=========================================================\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        double double_input{0.0};
        bb.take_input(double_input);

        std::cout<<"=========================================================\n";
    }
}
