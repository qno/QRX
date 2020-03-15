#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

TEST_CASE("Test1", "[xxx]")
{
  REQUIRE(1 == 1);
  REQUIRE(true == false);
}

TEST_CASE("Test2", "[yyy]")
{
  REQUIRE(2 == 1);
}

TEST_CASE("xxx", "[xxy]")
{
  REQUIRE("yyy" == "xxx");
}

TEST_CASE("aaa", "[aaa]")
{
  REQUIRE(1 + 1 == 2);
}

TEST_CASE("ddd", "[888")
{
  REQUIRE(true == 1);
}
