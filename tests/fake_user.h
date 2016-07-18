//
// Created by serg on 7/5/16.
//

#ifndef WS_SERVER_FAKE_USER_H_H
#define WS_SERVER_FAKE_USER_H_H

#include "user.h"

template <UserType user_type> class FakeUser : public User {
public:
    static void load(const std::string &name, std::function<void (User::Ptr)> callback)
    {
        if(user_type == UserType::UNKNOWN)
            return callback(nullptr);

        User::Ptr user = std::make_shared<User>(name);
        user->setType(user_type);

        return callback(user);
    }
};

#endif //WS_SERVER_FAKE_USER_H_H
