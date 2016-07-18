#include <websocketpp/close.hpp>
#include <websocketpp/frame.hpp>
#include "ws_server_impl.h"
#include <g3log/g3log.hpp>

using websocketpp::lib::thread;
using websocketpp::lib::mutex;
using websocketpp::lib::lock_guard;
using websocketpp::lib::unique_lock;
using websocketpp::lib::condition_variable;

WsServerImpl::WsServerImpl()
{
	_server.init_asio();

	_server.set_open_handler(websocketpp::lib::bind(&WsServerImpl::_onWsOpen,this,websocketpp::lib::placeholders::_1));
	_server.set_close_handler(websocketpp::lib::bind(&WsServerImpl::_onWsClose,this,websocketpp::lib::placeholders::_1));
	_server.set_message_handler(websocketpp::lib::bind(&WsServerImpl::_onWsMessage,this,websocketpp::lib::placeholders::_1,websocketpp::lib::placeholders::_2));
}

void WsServerImpl::run(uint16_t port)
{
	_port = port;
	try
	{

		_server.listen(_port);
		_server.start_accept();

		try
		{
			_server.run();
		}
		catch (const std::exception & e)
		{
		}

	}
	catch (const std::exception & e)
	{
	}

	while(true)
		std::this_thread::sleep_for(std::chrono::seconds(1));
}

void WsServerImpl::_close(Connection c)
{
	_server.close(c, websocketpp::close::status::normal, "");
}

void WsServerImpl::_send(Connection c, const std::string& data)
{
	_server.send(c, data, websocketpp::frame::opcode::TEXT);
}


void WsServerImpl::_onWsOpen(Connection hdl)
{
	_onOpen(hdl);
}

void WsServerImpl::_onWsClose(Connection hdl)
{
	_onClose(hdl);
}

void WsServerImpl::_onWsMessage(Connection hdl, websocketpp::server<websocketpp::config::asio>::message_ptr msg)
{
	_onMessage(hdl, msg->get_payload());
}
