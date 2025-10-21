#include "utils.hpp"
#include <catch2/catch_test_macros.hpp>
#include <vector>

double EPS = 1e-8;

bool compare_doubles(double left, double right)
{
    return abs(left - right) < EPS;
}

TEST_CASE("Чтение с файла", "[read_array_from_file]")
{
    std::vector<double> test_array;

    read_array_from_file("../../src/input.txt", test_array);

    REQUIRE(test_array.size() == 56);
    REQUIRE(compare_doubles(test_array[0], 0.0));
    REQUIRE(compare_doubles(test_array[55], 82500.0));
    REQUIRE(compare_doubles(test_array[25], 37500.0));
}