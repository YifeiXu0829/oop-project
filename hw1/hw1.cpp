#include <iostream>
#include "hw1.h"


int main()
{
    account test_account("3126109346", "yifeix@uchicago.edu", 200.666);
    test_account.add_transaction_for_this_account(12, "Monday", "food", "Friday");
    test_account.add_transaction_for_this_account(66, "Tuesday", "entertainment", "Friday");
    test_account.add_transaction_for_this_account(30.6, "Tuesday", "transportation", "Friday");
    test_account.add_transaction_for_this_account(1.5, "Friday", "food", "Friday");

    test_account.generate_report();
    test_account.send_report("reporter@example.com");
    return 0;
}
