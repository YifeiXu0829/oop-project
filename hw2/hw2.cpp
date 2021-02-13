#include "hw2.h"
#include "creditcard.h"
#include "paypal.h"
#include "bitcoin.h"

int main()
{
    ShoppingCart shopping_cart{new CreditCard()};

    shopping_cart.CallShoppingCart();

    shopping_cart.change_pay_method(new Paypal());

    shopping_cart.CallShoppingCart();

    shopping_cart.change_pay_method(new Bitcoin());

    shopping_cart.CallShoppingCart();
}
