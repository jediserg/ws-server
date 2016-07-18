//
// Created by serg on 7/4/16.
//
#ifndef WS_SERVER_POLICY_H
#define WS_SERVER_POLICY_H

#include <string>
#include <functional>
#include "user.h"

struct NoHash
{
    std::string operator()(const std::string msg)
    {
        return msg;
    }
};

template <class HashFunc = NoHash>class Policy
{
public:
    virtual bool auth(User::Ptr user, std::string hash, std::string ticket) = 0;
protected:
    HashFunc hashFunc;
};

#endif //WS_SERVER_POLICY_H
