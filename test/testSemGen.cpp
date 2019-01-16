//
// Created by Prakhar Agarwal on 2019-01-16.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Testing basic arithmetic", "[arithmetic]")
{
    int a = 1;
    int b = 2;
    REQUIRE(a != b);
    b = a;
    REQUIRE(a == b);
}
