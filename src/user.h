#pragma once

#include <memory>

namespace ws
{
	enum class UserType
	{
		UNKNOWN, ADMIN, USER
	};

	class User
	{
	public:

		using Ptr = std::shared_ptr<User>;

		User(std::string name, UserType type, std::string hash = "");

		~User();

		const std::string &getName() const;

		void setName(std::string name);

		UserType getType() const;

		void setType(UserType);

		const std::string &getHash() const;

	protected:
		std::string _name;
		UserType _type;
		std::string _hash;
	};
}