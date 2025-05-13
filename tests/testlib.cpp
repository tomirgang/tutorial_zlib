
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <tutorial_zlib/lib.hpp>

TEST_CASE("Quick check", "[main]")
{
    REQUIRE(6.0 == 6.0);
    REQUIRE(2.0 == Approx(2.0));
}
