//
// Created by serg on 7/4/16.
//
#include <gtest/gtest.h>
#include <net/simple_policy.h>
#include "fake_hash.h"


TEST(TestSimpleAuth, SimpleAuthTest) {
    SimpleAuthPolicy<FakeHashFunction> policy  {
            {"login1", "password"},
            {"login2", "password2"},
            {"login3", "password3"}
    };

    User::Ptr  user1 = std::make_shared<User>("login1");
    User::Ptr  user2 = std::make_shared<User>("login2");
    User::Ptr  user3 = std::make_shared<User>("login3");

    User::Ptr  user = std::make_shared<User>("login");

    EXPECT_TRUE(policy.auth(user1, "passwordtoken", "token"));
    EXPECT_FALSE(policy.auth(user1, "passwordtoken1", "token"));
    EXPECT_FALSE(policy.auth(user, "passwordtoken", "token"));
    EXPECT_FALSE(policy.auth(user, "passwordtoken", "token1"));

    EXPECT_TRUE(policy.auth(user2, "password2token", "token"));
    EXPECT_TRUE(policy.auth(user3, "password3token", "token"));
}
