//
// Created by serg on 7/5/16.
//
#include <gtest/gtest.h>
#include "net/auth.hpp"
#include "fake_policy.h"
#include "fake_user.h"
#include "net/simple_policy.h"

using namespace ws;

TEST(AuthTest, AuthTestFailed) {
    Auth<std::shared_ptr<int>, AlwaysFalseFakePolicy> auth;

    std::shared_ptr<int> con1 = std::make_shared<int>(1);
    std::shared_ptr<int> con2 = std::make_shared<int>(2);

    auth.addSession(con1);
    auth.addSession(con2);

    Session::Ptr session1 = auth.getSession(con1);
    Session::Ptr session2 = auth.getSession(con2);

    ASSERT_TRUE(session1);

    ASSERT_FALSE(session1->isAuthorized());
    EXPECT_GT(session1->getToken().length(), 5);

    auto response1 = auth.startAuth(session1);

    EXPECT_EQ(response1["error"].int_value(), 443);
    EXPECT_EQ(response1["msg"].string_value(), "Not authorized");
    EXPECT_EQ(response1["token"].string_value(), session1->getToken());

    EXPECT_TRUE(session1->isAuthRequestSent());

    auth.onAuthReply(session1, json11::Json::object{{"hash", "345"}}, [](json11::Json json){
       EXPECT_EQ(json["error"].string_value(), "Bad login or password");
    });

    ASSERT_FALSE(session1->isAuthorized());

    auth.onAuthReply(session1, json11::Json::object{{"login", "345"}}, [](json11::Json json){
        EXPECT_EQ(json["error"].string_value(), "Bad login or password");
    });

    ASSERT_FALSE(session1->isAuthorized());

    auth.onAuthReply(session2, json11::Json::object{{"login", "345"}, {"hash", "12345"}}, [](json11::Json json){
        EXPECT_EQ(json["error"].string_value(), "Bad login or password");
    });

    ASSERT_FALSE(session1->isAuthorized());
}

TEST(AuthTest, AuthTestSuccess) {
    Auth<std::shared_ptr<int>, AlwaysFalseFakePolicy> auth;

    std::shared_ptr<int> con1 = std::make_shared<int>(1);
    std::shared_ptr<int> con2 = std::make_shared<int>(2);

    auth.addSession(con1);
    Session::Ptr session1 = auth.getSession(con1);
    ASSERT_TRUE(session1);

    ASSERT_FALSE(session1->isAuthorized());

    auto response1 = auth.startAuth(session1);

    auth.onAuthReply(session1, json11::Json::object{{"login", "login"}, {"hash", "hash"}}, [](json11::Json json){
        EXPECT_EQ(json["result"].string_value(), "success");
    });

    EXPECT_TRUE(session1->isAuthorized());
}
