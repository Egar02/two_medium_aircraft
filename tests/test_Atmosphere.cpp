#include <Atmosphere.hpp>
#include <catch2/catch_test_macros.hpp>

double EPS = 1e-8;

bool compare_doubles(double left, double right)
{
    return abs(left - right) < EPS;
}

TEST_CASE("Вычисление геопотенциальной высоты", "[geopotential_height]")
{
    REQUIRE(compare_doubles(geopotential_height(0.0), 0.0));
    REQUIRE(compare_doubles(geopotential_height(1000.0), 999.8427121));
    REQUIRE(compare_doubles(geopotential_height(100000.0), 98451.23728));
}