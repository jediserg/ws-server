#pragma once

#include <memory>

enum class UserType {UNKNOWN, ADMIN, USER};

class User
{
public:

    using Ptr = std::shared_ptr<User>;

	User(const std::string& name, UserType type, std::string hash);
	~User();

	const std::string& getName();
	void setName(const std::string name);

	UserType getType();
	void setType(UserType);
protected:
    std::string _name;
    UserType _type;
    std::string _hash;
};