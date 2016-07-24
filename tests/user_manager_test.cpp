//
// Created by serg on 7/4/16.
//
#include <gtest/gtest.h>
#include "user_manager.h"

using namespace ws;

#include "net/simple_policy.h"


TEST(TestUserManager, TestUserManager)
{
    auto user1 = std::make_shared<User>("user1");
    auto user2 = std::make_shared<User>("user2");

    UserManager::instance().addUser(user1);
    UserManager::instance().addUser(user2);

    ASSERT_TRUE(UserManager::instance().getUser("user1"));
    ASSERT_TRUE(UserManager::instance().getUser("user2"));

    EXPECT_EQ(UserManager::instance().getUser("user1")->getName(), user1->getName());
    EXPECT_EQ(UserManager::instance().getUser("user2")->getName(), user2->getName());
}
