#include <iostream>
#include <vector>
#include <sstream>

struct NotificationEngine
{
    static void deliver(std::string from, std::string to, std::string subject, std::string_view report)
    {
        std::cout<<"report email sent"<<std::endl;
        std::cout<<"content:\n"<<report;
    }
};

class report_manager
{
public:
    virtual void generate_report() = 0;
    virtual void send_report(std::string from) = 0;
    virtual ~report_manager(){};

protected:
    std::ostringstream report_;
};

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

