#include <iostream>


struct Bitcoin : public PayMethod
{
    void pay() override
    {
        std::cout<<"Pay with Credit Bitcoin \n";
    }
};
