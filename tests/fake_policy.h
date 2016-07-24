//
// Created by serg on 7/5/16.
//

#ifndef WS_SERVER_FAKE_POLICY_H_H
#define WS_SERVER_FAKE_POLICY_H_H

using namespace ws;

#include "net/policy.h"
#include "fake_hash.h"

class AlwaysFalseFakePolicy : public Policy<FakeHashFunction> {
public:
    virtual bool auth(User::Ptr user, std::string hash, std::string ticket) override {
        return false;
    }
};
#endif //WS_SERVER_FAKE_POLICY_H_H
