#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

TEST_CASE( "Test1", "[xxx]" ) {
    REQUIRE( 1 == 1 );
}

TEST_CASE( "Test2", "[yyy]" ) {
    REQUIRE( 2 == 1 );
}

TEST_CASE( "xxx", "[xxy]") {
  REQUIRE( "xxx" == "yyy");
}
