#include <iostream>

struct CreditCard : public PayMethod
{
    void pay() override
    {
        std::cout<<"Pay with Credit Card \n";
    }
};
