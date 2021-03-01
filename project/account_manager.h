#pragma once

#include <iostream>
#include <tuple>
#include <string>

class account_manager
{
public:
    using string = std::string;
    
    // get into postgresql database to validate credential and get role info
    std::tuple<bool, char> validate_credential(string usrname, string password)
    {
        //return std::make_tuple(false, "");
        return std::make_tuple(true, 'T');
    }
};
