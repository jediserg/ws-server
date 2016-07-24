//
// Created by serg on 7/6/16.
//
#include <gtest/gtest.h>
#include "fake_ws_server_impl.h"
#include "net/server.hpp"
#include "fake_user.h"
#include "net/simple_policy.h"
using namespace ws;

TEST(ServerTests, ServerTests) {
    auto  policy = std::make_shared<NoAuthPolicy>();

    NetServer<FakeWsServerImpl, NoAuthPolicy> server;

    auto con = server.newConnection();
    ASSERT_TRUE(con);

    EXPECT_TRUE(server.getConnsctions()[con].is_oppened);

    server.recvMessage(con, json11::Json(json11::Json::object{{"command", "register"}}).dump());

    EXPECT_EQ(server.getConnsctions()[con].out_msg_cnt, 1);

    std::string err;
    auto response1 = json11::Json::parse(server.getConnsctions()[con].last_out, err);

    EXPECT_EQ(response1["error"].int_value(), 443);

    server.recvMessage(con, json11::Json(json11::Json::object{{"command", "login"}, {"login", "login"}, {"hash", "hash"}}).dump());
    auto response2 = json11::Json::parse(server.getConnsctions()[con].last_out, err);

    printf("response2-%s\n", response2.dump().c_str());

    EXPECT_EQ(response2["result"].string_value(), "success");

    HandlerManager::instance().addHandler("test", [](Session::Ptr s, const json11::Json& json, HandlerCallback&& callback) {
        EXPECT_EQ(json["test"].string_value(), "QwErTy12345");
        callback(json11::Json(json11::Json::object{{"test_result", "test_result12345"}}));
    });

    server.recvMessage(con, json11::Json(json11::Json::object{{"command", "test"}, {"test", "QwErTy12345"}}).dump());
    auto response3 = json11::Json::parse(server.getConnsctions()[con].last_out, err);

    EXPECT_EQ(response3["test_result"].string_value(), "test_result12345");
}
