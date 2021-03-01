#include <iostream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

void PostgreConnectionTest()
{
    try {
        connection C("dbname = emails user = postgres password = Abcd1234 \
            hostaddr = 127.0.0.1 port = 5432");
        if (C.is_open()) {
            cout << "Opened database successfully: " << C.dbname() << endl;
        } else {
            cout << "Can't open database" << endl;
        }
        // do things

        C.close();
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        std::exit(1);
    }
}

int main()
{
    PostgreConnectionTest();
    return 0;
}
