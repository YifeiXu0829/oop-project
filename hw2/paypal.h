#include <iostream>


struct Paypal : public PayMethod
{
    void pay() override
    {
        std::cout<<"Pay with Paypal \n";
    }
};
