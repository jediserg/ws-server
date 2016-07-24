#pragma once

#include "policy.h"
#include "net/policy.h"
#include <map>
#include <string>
#include <g3log/g3log.hpp>
#include <initializer_list>

namespace ws
{
    typedef std::map<std::string, std::string> LoginPasswordMap;

    template<class HashFunction>
    class SimpleAuthPolicy : public Policy<HashFunction>
    {
    public:
        SimpleAuthPolicy(std::initializer_list<std::pair<std::string, std::string> > l)
        {
            for(auto rec : l)
            {
                _map[rec.first] = rec.second;
            }
        }

        bool auth(User::Ptr user, std::string hash, std::string ticket) override
        {
            if(!user)
                return false;

            auto it = _map.find(user->getName());

            if(it == _map.end())
                return false;

            const std::string &password = it->second;

            std::string storedHash = this->hashFunc(password + ticket);
            return hash == storedHash;
        }


    private:
        LoginPasswordMap _map;
    };

    class NoAuthPolicy : public Policy<>
    {
    public:
        virtual bool auth(User::Ptr user, std::string hash, std::string ticket) override
        {
            return true;
        }
    };
}