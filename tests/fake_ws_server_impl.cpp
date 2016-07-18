//
// Created by serg on 7/6/16.
//
#include "fake_ws_server_impl.h"

FakeWsServerImpl::FakeWsServerImpl() {

}

void FakeWsServerImpl::_close(Connection c) {
    auto info = _map.find(c);

    if(info == _map.end())
        return;

    info->second = {.is_oppened = true, .in_msg_cnt = 0, .out_msg_cnt = 0};
    _onClose(c);
}

void FakeWsServerImpl::_send(Connection c, std::string data) {
    auto info = _map.find(c);

    if(info == _map.end())
        return;

    info->second.out_msg_cnt++;
    info->second.last_out = data;
}

FakeWsServerImpl::ConnectionMap &FakeWsServerImpl::getConnsctions() {
    return _map;
}

FakeWsServerImpl::Connection FakeWsServerImpl::newConnection() {
    static int last_id = 1;

    Connection con = std::make_shared<int>(last_id++);

    ConnectionInfo info {.is_oppened = true, .in_msg_cnt = 0, .out_msg_cnt = 0};
    _map[con] = info;

    _onOpen(con);

    return con;
}

void FakeWsServerImpl::recvMessage(Connection c, std::string msg) {
    auto info = _map.find(c);

    if(info == _map.end())
        return;

    info->second.last_in = msg;
    info->second.in_msg_cnt++;

    _onMessage(c, msg);
}













