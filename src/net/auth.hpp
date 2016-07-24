#pragma once

#include "session.hpp"
#include "json11.hpp"
#include <map>
#include <g3log/g3log.hpp>
#include <user.h>
#include <handler_manager.h>
#include <user_manager.h>
#include "handler.h"

namespace ws
{
	template<class Connection, class Policy>
	class Auth
	{
	public:
		typedef std::map<Connection, Session::Ptr, std::owner_less<Connection> > SessionMap;
		typedef std::shared_ptr<Policy> PolicyTypePtr;

		Auth()
		{
			HandlerManager::instance().addHandler("register", [this](Session::Ptr session, const json11::Json &json,
																	 HandlerCallback &&callback)
				{
					callback(this->startAuth(session));
				});

			HandlerManager::instance().addHandler("login", [this](Session::Ptr session, const json11::Json &json,
																  HandlerCallback &&callback)
				{
					this->onAuthReply(session, json, callback);
				});
		}

		void addSession(Connection connection)
		{
			Session::Ptr session = std::make_shared<Session>();
			_sessions[connection] = session;
		}

		json11::Json startAuth(Session::Ptr session)
		{
			session->setAuthRequestSent();

			return json11::Json::object {
					{"error", 443},
					{"msg",   "Not authorized"},
					{"token", session->getToken()}
			};
		}

		Session::Ptr getSession(Connection c)
		{
			auto it = _sessions.find(c);

			if(it == _sessions.end())
				return Session::Ptr();

			return it->second;
		}

		void onAuthReply(Session::Ptr session, json11::Json json, std::function<void(json11::Json &&)> callback)
		{
			std::string login = json["login"].string_value();

			if(login.empty())
				return callback(json11::Json::object {{"error", "Bad login or password"}});

			std::string hash = json["hash"].string_value();

			if(hash.empty())
			{
				return callback(json11::Json::object {{"error", "Bad login or password"}});
			}

			UserManager::instance().loadUser(login, [callback, session, this, hash](User::Ptr user)
				{
					if(user)
					{
						session->setUser(user);
						session->authorize(true);

						if(this->_policy->auth(user, hash, session->getToken()))
						{
							return callback(json11::Json::object {{"result", "success"}});
						}
						else
						{
							return callback(json11::Json::object {{"error", "Bad login or password"}});
						}
					}

					return callback(json11::Json::object {{"error", "Couldn't load user"}});
				});


		}

	private:
		PolicyTypePtr _policy;

		SessionMap _sessions;
	};
}