#include "utils.hpp"
#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <filesystem>

double EPS = 1e-8;

bool compare_doubles(double left, double right)
{
    return abs(left - right) < EPS;
}

TEST_CASE("Чтение массива с файла", "[read_array_from_file]")
{
    std::vector<double> test_array;

    read_array_from_file("../../src/input.txt", test_array);

    REQUIRE(test_array.size() == 56);
    REQUIRE(compare_doubles(test_array[0], 0.0));
    REQUIRE(compare_doubles(test_array[55], 82500.0));
    REQUIRE(compare_doubles(test_array[25], 37500.0));
}

TEST_CASE("Чтение с json-файла", "read_json")
{
    nlohmann::json json_file;

    std::filesystem::path current_path = std::filesystem::current_path();
    std::cout << "Текущая директория: " << current_path << std::endl;

    read_json("../../src/data/density.json", json_file);

    std::unordered_map<double, double> densities;

    for (const auto& item : json_file)
    {
        densities[item["height"]] = item["rho"];
    }

    REQUIRE(densities.size() == 12);
    REQUIRE(compare_doubles(densities[0.0], 1.478079263048531));
    REQUIRE(compare_doubles(densities[47.0], 1.427529564820696e-3));
    REQUIRE(compare_doubles(densities[120.0], 2.440384595331594e-8));

}