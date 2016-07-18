//
// Created by serg on 6/28/16.
//

#ifndef WS_SERVER_USER_MANAGER_H
#define WS_SERVER_USER_MANAGER_H

#include <memory>
#include <map>
#include "user.h"
#include "json11.hpp"
#include <functional>

class UserManager
{
public:
    using UserFactoryCallback = std::function<void (User::Ptr)>;
    using UserFactoryFunc = std::function<void (std::string, UserFactoryCallback)>;
    void addUser(User::Ptr user);

    User::Ptr getUser(const std::string& login);
    static UserManager& instance();

    void loadUser(const std::string &name, UserFactoryCallback callback);

    void setFactory(UserFactoryFunc f);
private:
    std::map<std::string, User::Ptr> _users;
    UserFactoryFunc _factory;
};


#endif //WS_SERVER_USER_MANAGER_H
