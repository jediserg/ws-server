#pragma once

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <memory>
#include "user.h"

namespace ws
{
	class Session
	{
	public:
		using Ptr = std::shared_ptr<Session>;

		Session()
				: is_authorized(false),
				  is_auth_request_sent(false)
		{
			_token = boost::uuids::to_string(boost::uuids::random_generator()());
		}

		~Session()
		{ }

		const std::string &getToken() const
		{ return _token; }

		User::Ptr getUser()
		{ return _data; }

		void setUser(User::Ptr data)
		{ _data = data; }

		bool isAuthorized() const
		{
			return is_authorized;
		}

		void authorize(bool is_authorized)
		{
			Session::is_authorized = is_authorized;
		}

		bool isAuthRequestSent() const
		{
			return is_auth_request_sent;
		}

		void setAuthRequestSent()
		{
			is_auth_request_sent = true;
		}

	private:
		User::Ptr _data;
		std::string _token;

		bool is_authorized;

	private:
		bool is_auth_request_sent;
	};
}