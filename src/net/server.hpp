#pragma once

#include <thread>
#include <chrono>
#include "session.hpp"
#include "auth.hpp"
#include <functional>
#include <exception>
#include <iostream>
#include <handler_manager.h>

#include "../user.h"

template <class Impl, class AuthPolicy> class NetServer: public Impl
{
public:
	typedef Auth<typename Impl::Connection, AuthPolicy> AuthType;

	NetServer(std::shared_ptr<AuthPolicy> p)
		: 	_auth(p)
	{
		
	}

	virtual ~NetServer()
	{

	}

private:
	void _send(typename Impl::Connection c, const json11::Json& json)
	{
		std::string str;

		try
		{
			str = json.dump();
		}
		catch(std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}

		Impl::_send(c, str);
	}

	void _onOpen(typename Impl::Connection hdl) override
	{
        _auth.addSession(hdl);
	}

	void _onClose(typename Impl::Connection hdl) override
	{
	}

	void _onMessage(typename Impl::Connection hdl, const std::string& msg) override
	{
		auto s = _auth.getSession(hdl);

		if(!s)
		{
			this->_close(hdl);
			return;
		}

		std::string err;
		json11::Json packet = json11::Json::parse(msg, err);

		if(!err.empty())
		{
			_send(hdl, json11::Json::object {
				{"err", err}
			});
			return;
		}

		auto str_command = packet["command"].string_value();

		if(str_command.empty())
		{
			_send(hdl, json11::Json::object {
				{"err", "No command"}
			});
			return;
		}

        auto user = s->getUser();

        HandlerPermission permissions;

        if(!user)
            permissions = HandlerPermission::ANYONE;
        else
            permissions = user->getType() == UserType::ADMIN ? HandlerPermission::ADMIN : HandlerPermission::USER;


		auto handler = HandlerManager::instance().getHandler(str_command, permissions);

		if(!handler)
        {
			_send(hdl, json11::Json::object {
				{"err", "Unknown command"}
			});

			return;
		}

		(*handler)(s, packet, std::bind(&NetServer::_send, this, hdl, std::placeholders::_1));
	}

	AuthType _auth;
};