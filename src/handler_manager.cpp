//
// Created by serg on 6/28/16.
//

#include "handler_manager.h"

namespace ws
{

    bool HandlerManager::addHandler(const std::string &command, Handler h, HandlerPermission p)
    {
        _handlers[command] = {.handler = h, .permissions = p};

        return true;
    }

    boost::optional<Handler> HandlerManager::getHandler(const std::string &command, HandlerPermission permission)
    {
        const auto &it = _handlers.find(command);

        if(it == _handlers.end())
            return boost::optional<Handler>();

        if(checkPermissions(permission, it->second.permissions))
            return boost::optional<Handler>(it->second.handler);
        else
            return boost::optional<Handler>();
    }

    bool HandlerManager::checkPermissions(const HandlerPermission &user_permissions,
                                          const HandlerPermission &handler_permissions) const
    {
        if(user_permissions == HandlerPermission::ADMIN)
            return true;

        if(user_permissions == HandlerPermission::USER && handler_permissions != HandlerPermission::ADMIN)
            return true;

        return user_permissions == HandlerPermission::ANYONE && handler_permissions == HandlerPermission::ANYONE;
    }

    HandlerManager &HandlerManager::instance()
    {
        static HandlerManager instance;
        return instance;
    }
}



