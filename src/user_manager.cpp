//
// Created by serg on 6/28/16.
//

#include <g3log/logworker.hpp>
#include <g3log/g3log.hpp>
#include <iostream>
#include "user_manager.h"

void UserManager::addUser(User::Ptr user)
{
	_users[user->getName()] = user;
}

User::Ptr UserManager::getUser(const std::string& name)
{
	auto it = _users.find(name);

	if(it == _users.end())
		return User::Ptr();

	return it->second;
}

UserManager &UserManager::instance()
{
	static UserManager instance;

	return instance;
}

void UserManager::setFactory(UserFactoryFunc f) {
    _factory = f;
}

void UserManager::loadUser(const std::string &name, UserFactoryCallback callback) {
    _factory(name, callback);
}







