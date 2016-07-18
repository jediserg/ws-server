//
// Created by serg on 7/2/16.
//
#include <gtest/gtest.h>
#include "user.h"

TEST(UserTest, TestUserGetterSetters) {
    User u("test_user");
    u.setType(UserType::ADMIN);

    EXPECT_EQ("test_user", u.getName());
    EXPECT_EQ(UserType::ADMIN, u.getType());

    u.setName("new_name");

    EXPECT_EQ(u.getName(), "new_name");
}
