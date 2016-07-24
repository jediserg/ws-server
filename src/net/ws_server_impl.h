#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

namespace ws
{
    class WsServerImpl
    {
    public:
        typedef websocketpp::connection_hdl Connection;

        WsServerImpl();

        void run(uint16_t port);

        void _close(Connection c);

    protected:
        void _send(Connection c, const std::string &data);

        virtual void _onOpen(Connection) = 0;

        virtual void _onClose(Connection) = 0;

        virtual void _onMessage(Connection, const std::string &) = 0;

    private:
        void _onWsOpen(Connection hdl);

        void _onWsClose(Connection hdl);

        void _onWsMessage(Connection hdl, websocketpp::server<websocketpp::config::asio>::message_ptr msg);

        uint16_t _port;

        websocketpp::server<websocketpp::config::asio> _server;
    };
}