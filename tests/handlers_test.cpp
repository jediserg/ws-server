//
// Created by serg on 7/4/16.
//
#include <gtest/gtest.h>
#include "handler_manager.h"

using namespace ws;

void fun1(Session::Ptr s, const json11::Json& j, HandlerCallback&& h)
{

}

void fun2(Session::Ptr s, const json11::Json& j, HandlerCallback&& h)
{

}

void fun3(Session::Ptr s, const json11::Json& j, HandlerCallback&& h)
{

}

TEST(TestHandlers, Testhandleres)
{
    HandlerManager::instance().addHandler("command1", fun1);
    HandlerManager::instance().addHandler("command2", fun2, HandlerPermission::ADMIN);

    RegisterHandler rh("command3", fun3, HandlerPermission::USER);

    EXPECT_TRUE(HandlerManager::instance().getHandler("command1", HandlerPermission::ANYONE));
    EXPECT_TRUE(HandlerManager::instance().getHandler("command1", HandlerPermission::ADMIN));
    EXPECT_TRUE(HandlerManager::instance().getHandler("command1", HandlerPermission::USER));

    EXPECT_TRUE(HandlerManager::instance().getHandler("command2", HandlerPermission::ADMIN));
    EXPECT_FALSE(HandlerManager::instance().getHandler("command2", HandlerPermission::USER));
    EXPECT_FALSE(HandlerManager::instance().getHandler("command2", HandlerPermission::ANYONE));

    EXPECT_TRUE(HandlerManager::instance().getHandler("command3", HandlerPermission::USER));
    EXPECT_FALSE(HandlerManager::instance().getHandler("command3", HandlerPermission::ANYONE));
    EXPECT_TRUE(HandlerManager::instance().getHandler("command3", HandlerPermission::ADMIN));

    EXPECT_FALSE(HandlerManager::instance().getHandler("command4", HandlerPermission::ANYONE));
}
