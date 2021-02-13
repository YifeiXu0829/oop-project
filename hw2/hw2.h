class PayMethod
{
public:
    virtual ~PayMethod(){}
    virtual void pay() = 0;
    //virtual void postpay() = 0;
};

class ShoppingCart final
{
public:
    ShoppingCart(PayMethod* m):pay_method_(m)
    {}

    void CallShoppingCart()
    {
        pay_method_->pay();
        //pay_method_->postpay();
    }

    void change_pay_method(PayMethod* m)
    {
        if(pay_method_ != nullptr)
        {
            delete pay_method_;
        }

        pay_method_ = m;
    }

    ~ShoppingCart()
    {
        if(pay_method_ != nullptr)
        {
            delete pay_method_;
        }
    }
private:
    PayMethod* pay_method_ = nullptr;
};
