//
// Created by serg on 7/4/16.
//

#include <gtest/gtest.h>
#include "my_factory.h"

class Base {
public: Base() {}
    virtual const char* getType() = 0;
};

class Foo : public Base
{
public:
    constexpr static const char* TYPE = "Foo";

    virtual const char *getType() override {
        return TYPE;
    }


};

class Bar : public Base
{
public:
    constexpr static const char* TYPE = "Bar";

    virtual const char *getType() override {
        return TYPE;
    }
};

TEST(MyFactoryTests, MyFactoryTest) {
    MyFactory<Base> factory {
            FACTORY_ADD(Base, Foo),
            FACTORY_ADD(Base, Bar)
    };

    EXPECT_TRUE(factory.create("Foo"));
    EXPECT_TRUE(factory.create("Bar"));
    EXPECT_FALSE(factory.create("NoInTheFactory"));

    EXPECT_EQ("Foo", factory.create("Foo")->getType());
    EXPECT_EQ("Bar", factory.create("Bar")->getType());
}
