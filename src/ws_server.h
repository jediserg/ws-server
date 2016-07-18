//
// Created by serg on 7/7/16.
//

#ifndef WS_SERVER_WS_SERVER_H
#define WS_SERVER_WS_SERVER_H

#include <net/ws_server_impl.h>
#include "net/server.hpp"
#include "net/simple_policy.h"
#include "utils/md5.h"

//template <class AuthPolicy, class UserCls> using WsServer = NetServer<AuthPolicy, UserCls, WsServerImpl>;

class WsServerNoAuth : public NetServer<WsServerImpl, NoAuthPolicy> {
public:

};
//template <class UserCls> using WsSimpleServer = NetServer<SimpleAuthPolicy<MD5Hash>, UserCls, WsServerImpl>;

#endif //WS_SERVER_WS_SERVER_H
