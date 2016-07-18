//
// Created by serg on 7/5/16.
//

#ifndef WS_SERVER_FAKE_HASH_H_H
#define WS_SERVER_FAKE_HASH_H_H


#include <string>

struct FakeHashFunction
{
    std::string operator()(const std::string& hash)
    {
        return  hash;
    }
};

#endif //WS_SERVER_FAKE_HASH_H_H
