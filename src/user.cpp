#include "user.h"
#include <cpptoml.h>
#include <g3log/g3log.hpp>

User::~User()
{

}

const std::string& User::getName()
{
	return _name;
}

void User::setName(const std::string name)
{
	_name = name;
}

UserType User::getType()
{
	return _type;
}

void User::setType(UserType t)
{
	_type = t;
}

User::User(const std::string &name, UserType type, std::string hash)
        : _name(name), _type(type), _hash(hash) {

}




