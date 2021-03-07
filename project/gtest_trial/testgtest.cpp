#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

enum Role
{
    Student,
    Faculty,
    Admin
};

class AccountManager
{
public:
    AccountManager()
    {
        this->add_credential("testuser1", "pw1", Role::Student);
        this->add_credential("testuser2", "pw2", Role::Faculty);
        this->add_credential("testuser3", "pw3", Role::Admin);
    }
    virtual ~AccountManager(){}
    virtual void login_with_credentials(std::string username,std::string password, Role role)
    {
        for (const auto& credential : dummy_credentials_)
        {
            if(username == std::get<0>(credential) && password == std::get<1>(credential) && role == std::get<2>(credential))
            {
                this->login_success_and_proceed();
            }
        }
    }
    virtual void add_credential(std::string username,std::string password, Role role)
    {
        dummy_credentials_.emplace_back(username, password, role);
    }

    virtual void login_success_and_proceed()
    {

    }
private:
    std::vector<std::tuple<std::string, std::string, Role>> dummy_credentials_;

};

class MockAccountManager : public AccountManager {
public:
   MOCK_METHOD(void, login_with_credentials, (std::string username,std::string password, Role role), (override));
   MOCK_METHOD(void, login_success_and_proceed, (), (override));
};

TEST(sample_test_case, sample_test)
{
    MockAccountManager mock_impl;
    EXPECT_CALL(mock_impl, login_success_and_proceed()).Times(1);

    mock_impl.login_with_credentials("testuser3", "pw3", Role::Admin);
}
