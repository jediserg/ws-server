//
// Created by serg on 7/5/16.
//
#include <gtest/gtest.h>
#include "utils/md5.h"

using namespace ws;

TEST(TestMD5, Testmd5) {
    MD5Hash hashFunc;

    EXPECT_EQ(hashFunc("Test"), "0cbc6611f5540bd0809a388dc95a615b");
    EXPECT_EQ(hashFunc("Test1"), "e1b849f9631ffc1829b2e31402373e3c");
}
