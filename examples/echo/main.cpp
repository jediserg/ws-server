//
// Created by serg on 7/7/16.
//
#include "ws_server.h"
#include "handler.h"

int main(int argc, char** argv)
{
    ws::WsServerNoAuth server;

    ws::RegisterHandler("echo", [](ws::Session::Ptr session, const json11::Json &json, ws::HandlerCallback &&callback)
        {
        callback(json11::Json::object{{"msg", json["msg"]}});
    });

    server.run(9002);

    return 0;
}
