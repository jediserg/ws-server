//
// Created by serg on 7/8/16.
//
#include "simple_user_factory.h"

namespace ws
{
    std::function<User::Ptr(std::string)> createSimpleUserFactory(
            std::map<std::string, std::pair<UserType, std::string>> &&users)
    {
        return [users](std::string name)
            {
                auto it = users.find(name);

                if(it == users.end())
                    return User::Ptr();

                return std::make_shared<User>(name, it->second.first, it->second.second);
            };
    }
}
