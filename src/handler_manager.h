#ifndef WS_SERVER_HANDLER_MANAGER_H
#define WS_SERVER_HANDLER_MANAGER_H

#include "handler.h"
#include <boost/optional.hpp>

namespace ws
{

    struct HandlerInfo
    {
        //HandlerInfo(Handler h, HandlerPermission p) : handler(h), permissions(p)
        //{}
        Handler handler;
        HandlerPermission permissions;
    };

    class HandlerManager
    {
    public:
        bool addHandler(const std::string &command, Handler h, HandlerPermission p = HandlerPermission::ANYONE);

        boost::optional<Handler> getHandler(const std::string &command, HandlerPermission permission);

        static HandlerManager &instance();

    private:
        std::map<std::string, HandlerInfo> _handlers;

        bool checkPermissions(const HandlerPermission &user_permissions,
                              const HandlerPermission &handler_permissions) const;
    };
}
#endif //WS_SERVER_HANDLER_MANAGER_H
