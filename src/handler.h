#pragma once

#include <functional>
#include <json11.hpp>
#include "net/session.hpp"

namespace ws
{

#define ADD_HANDLER(X, Y) static RegisterHandler handler_##X(#X, Y)

    enum class HandlerPermission
    {
        ANYONE, USER, ADMIN
    };

    using HandlerCallback = std::function<void(json11::Json &&)>;
    using Handler = std::function<void(Session::Ptr, const json11::Json &, HandlerCallback &&)>;

    struct RegisterHandler
    {
        RegisterHandler(const std::string &name, Handler handler,
                        HandlerPermission permissions = HandlerPermission::ANYONE);
    };
}
