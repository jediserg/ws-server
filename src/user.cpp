#include "user.h"
#include <cpptoml.h>
#include <g3log/g3log.hpp>

namespace ws
{
	User::~User()
	{

	}

	const std::string &User::getName() const
	{
		return _name;
	}

	void User::setName(std::string name)
	{
		_name = std::move(name);
	}

	UserType User::getType() const
	{
		return _type;
	}

	void User::setType(UserType t)
	{
		_type = t;
	}

	User::User(std::string name, UserType type, std::string hash)
			: _name(std::move(name)), _type(type), _hash(std::move(hash))
	{

	}

	const std::string &User::getHash() const
	{
		return _hash;
	}
}






