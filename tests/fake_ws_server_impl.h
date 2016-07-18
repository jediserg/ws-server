//
// Created by serg on 7/6/16.
//

#ifndef WS_SERVER_FAKE_WS_SERVER_IMPL_H_H
#define WS_SERVER_FAKE_WS_SERVER_IMPL_H_H

#include <memory>
#include <map>

struct ConnectionInfo
{
    bool is_oppened;
    int in_msg_cnt;
    int out_msg_cnt;

    std::string last_in;
    std::string last_out;
};

class FakeWsServerImpl
{
public:
    using Connection = std::shared_ptr<int>;
    using ConnectionMap = std::map<Connection, ConnectionInfo, std::owner_less<Connection>>;

    FakeWsServerImpl();
    void _close(Connection c);

    Connection newConnection();
    void recvMessage(Connection c, std::string msg);

    ConnectionMap& getConnsctions();
protected:
    void _send(Connection c, std::string data);
    virtual void _onOpen(Connection) = 0;
    virtual void _onClose(Connection) = 0;
    virtual void _onMessage(Connection, const std::string&) = 0;
private:
    ConnectionMap _map;
};
#endif //WS_SERVER_FAKE_WS_SERVER_IMPL_H_H
