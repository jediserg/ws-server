//
// Created by serg on 7/8/16.
//

#ifndef WS_SERVER_SIMPLE_USER_FACTORY_H
#define WS_SERVER_SIMPLE_USER_FACTORY_H

#include <map>
#include "user.h"

User::Ptr noAuthUserFactory(std::string)
{
    return nullptr;
};

std::function<User::Ptr (std::string)> createSimpleUserFactory(std::map<std::string, std::pair<UserType , std::string>> users);



#endif //WS_SERVER_SIMPLE_USER_FACTORY_H
