#include <iostream>
#include <vector>
#include <sstream>

/// the original code problems:
/// 1. account and coressponding transactions should not be accessed to FinancialReportNotificationManager
/// 2. transactions should only exist inside a coressponding account, should not exit independently outside account.
/// 3. account and transaction 's constructor reveal too much information (? not sure)
/// 4. NotificationEngine does not have to be created every time a delivery is requested.
/// 5. FinancialReportNotificationManager can be an adaptor of account class to helper it generate/send report of an account

/////////////////////////////////////////////////////////////
/// how my solution handles it:
/// 1. added a public call of add_transaction_for_this_account in account class so that transactions only lives as long as the account.
/// 2. following (1.), transactions will only live inside of a corresponding account and without having access to outside objects.
/// 3. deleted default constructor for account and transaction class, any new instances of them should be explicitly created of a certain constructor.
/// 4. made deliver a static method in NotificationEngine.
/// 5. made FinancialReportNotificationManager an abstract class (interface), and let account class derived from it so that reports can be generated as to the account instance.

struct NotificationEngine
{
    static void deliver(std::string from, std::string to, std::string subject, std::string_view report)
    {
        std::cout<<"report email sent"<<std::endl;
        std::cout<<"content:\n"<<report;
    }
};

// abstract interface class as a parent class of account class, provide report generate and send interface to user
class report_manager
{
public:
    virtual void generate_report() = 0;
    virtual void send_report(std::string from) = 0;
    virtual ~report_manager(){};

protected:
    std::ostringstream report_;
};

// transaction objects should be only owned by account objects, no transaction should exist without a coressponding account.
class transaction
{
public:
    explicit transaction(double amount, std::string date, std::string type, std::string created_at):amount_(amount), date_(date), type_(type), created_at_(created_at)
    {}
    transaction() = delete;

    friend std::ostream& operator<<(std::ostream&, const transaction&);

private:
    double amount_ = 0;
    std::string date_ = {};
    std::string type_ = {};
    std::string created_at_ = {};
};

std::ostream& operator<<(std::ostream& out, const transaction& tran)
{
    out << "amount:" << tran.amount_ << " type:" << tran.type_ << " created_at:" << tran.created_at_;
    return out;
}

// the account object should only be explicitly created, also as an implementation of report_manager, to have the ability to generate/send reports.
class account : public report_manager
{
public:
    explicit account(std::string acc_number, std::string email, double balance):acc_number_(acc_number), email_(email), balance_(balance)
    {}

    // delete default constructor and force it to explicit create an account
    account() = delete;
    // delete copy constructor
    account(const account&) = delete;
    ~account(){}

    void add_transaction_for_this_account(double amount, std::string date, std::string type, std::string created_at)
    {
        transactions_.emplace_back(amount, date, type, created_at);
    }

    void generate_report() override
    {
        for(const auto& tran : transactions_)
        {
            report_ << tran << "\n";
        }
    }

    void send_report(std::string from) override
    {
         NotificationEngine::deliver(from, email_, "your report", report_.str());
    }

private:
    std::string acc_number_ = {};
    std::string email_ = {};
    double balance_ = 0;

    // transactions should only be owned by the corresponding account
    std::vector<transaction> transactions_;
};

