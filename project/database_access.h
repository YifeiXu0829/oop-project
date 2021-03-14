#include <iostream>
#include <tuple>
#include <cassert>
#include <pqxx/pqxx>
#include "leveldb/db.h"


using namespace std;
using namespace pqxx;

class database_access_interface
{
public:
    database_access_interface()
    {
        try
        {
            conn_ = connection("dbname = regie user = postgres password = Abcd1234 \
                   hostaddr = 127.0.0.1 port = 5432");
            if (conn_.is_open())
            {
                //cout << "Opened database successfully: " << conn_.dbname() << endl;
            }
            else
            {
                cout << "Can't open database" << endl;
                std::exit(1);
            }
        }
        catch (const std::exception &e)
        {
            cerr << e.what() << std::endl;
            std::exit(1);
        }
    }

    virtual ~database_access_interface()
    {
        conn_.close();
    }
protected:
    auto transaction(std::string sql)
    {
        try
        {
            work W(conn_);
            W.exec(sql);
            W.commit();
            std::cout << "transaction success\n";
            return true;
        }
        catch (const std::exception &e)
        {
            cerr << e.what() << std::endl;
        }

        return false;
    }

    std::tuple<result, bool> select(std::string sql)
    {
        try
        {
            pqxx::nontransaction N(conn_);
            result R( N.exec( sql ));
            return {R, true};
        }
        catch (const std::exception &e)
        {
            cerr << e.what() << std::endl;
        }

        return {result{},false};
    }
private:
    connection conn_;
};

class account_tables_access final : public database_access_interface
{
private:
    leveldb::DB* db;
public:
    account_tables_access()
    {
        leveldb::Options options;
        options.create_if_missing = true;
        leveldb::Status status = leveldb::DB::Open(options, "/tmp/user_registered_courses", &db);
        assert(status.ok());
    }

    ~account_tables_access()
    {
        delete db;
    }

    void list_all_accounts()
    {
        std::string sql = "select username,role from accounts";
        auto [R, ok] = select(sql);
        if (!ok) return;
        for (const auto& c : R)
        {
            cout<<"user:"<<c[0].as<string>()<<" role:"<<c[1].as<string>()<<std::endl;
        }
    }

    bool add_user(std::string username, std::string pw, std::string role)
    {
        std::string sql = "insert into accounts(username,password,role) values('"+ username + "','"+ pw +"','"+ role +"');";
        return transaction(sql);
    }

    bool modify_user(std::string username, std::string pw, std::string role)
    {
        std::string sql = "update accounts set pw = '"+ pw +"', role='"+role+"' where username='"+username+"'";
        return transaction(sql);
    }

    bool delete_user(std::string username)
    {
        std::string sql = "delete from accounts where username='"+username+"'";
        return transaction(sql);
    }

    std::tuple<bool, char> validate_credential(string username, string password)
    {
        std::string sql = "select role from accounts where username='" + username + "' and password='" + password + "'";
        auto [R, ok] = select(sql);
        if (!R.size()) return {false, ' '};
        if (R.size() > 1)
        {
            cout<<"[warning] detected same user multiple accounts,return first one\n";
        } 
        return {true, (char)R.begin()[0].as<string>()[0]};
    }
};

class course_tables_access : public database_access_interface
{
public:
    course_tables_access()
    {
    }
    void list_all_courses()
    {
        std::string sql = "select course_name,capacity, instructor from courses";
        auto [R, ok] = select(sql);
        if (!ok) return;
        for (const auto& c : R)
        {
            cout<<"course:"<<c[0].as<string>()<<" capacity:"<<c[1].as<int>()<<" instructor:"<<c[2].as<string>()<<std::endl;
        }
    }

    bool find_course(string name)
    {
        std::string sql = "select course_name,capacity, instructor from courses where course_name='" + name + "'";
        auto [_, ok] = select(sql);
        return ok;
    }

    bool add_course(string name, int cap, string instructor)
    {
        std::string sql = "insert into courses(course_name,capacity,instructor) values('"+name+"', "+ std::to_string(cap) +", '"+instructor+"')";
        return transaction(sql);
    }

    bool delete_course(string name)
    {
        std::string sql = "delete from courses where course_name='"+ name +"'";
        return transaction(sql);
    }
};
