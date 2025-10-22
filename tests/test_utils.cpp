#include "utils.hpp"
#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <functional>

double EPS = 1e-8;

bool compare_doubles(double left, double right)
{
    return abs(left - right) < EPS;
}

bool compare_vectors(std::vector<double> &left, std::vector<double> &right)
{
    for (int i = 0; i < left.size(); ++i)
    {
        if (!compare_doubles(left[i], right[i]))
        {
            return false;
        }
    }

    return true;
}

double some_func(double num)
{
    return abs(num) * num;
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

    for (const auto &item : json_file)
    {
        densities[item["height"]] = item["rho"];
    }

    REQUIRE(densities.size() == 12);
    REQUIRE(compare_doubles(densities[0.0], 1.478079263048531));
    REQUIRE(compare_doubles(densities[47.0], 1.427529564820696e-3));
    REQUIRE(compare_doubles(densities[120.0], 2.440384595331594e-8));
}

TEST_CASE("Тест функции apply_func, лямбда-функция", "[apply_func]")
{
    std::vector<double> sample{0.0, 1.0, 2.0, 3.0, 4.0, 5.0};

    std::vector<double> sqr_sample;
    std::vector<double> sqr_exp{0.0, 1.0, 4.0, 9.0, 16.0, 25.0};

    auto sqr = [](double a)
    {
        return a * a;
    };

    apply_func(sqr, sample, sqr_sample);

    REQUIRE(sqr_sample.size() == sqr_exp.size());
    REQUIRE(compare_vectors(sqr_sample, sqr_exp));
}

TEST_CASE("Тест функции apply_func, обычная функция", "[apply_func]")
{
    std::vector<double> sample{0.0, -1.0, 2.0, -3.0, 4.0, -5.0};

    std::vector<double> func_sample;
    std::vector<double> func_exp{0.0, -1.0, 4.0, -9.0, 16.0, -25.0};

    apply_func(some_func, sample, func_sample);

    REQUIRE(func_sample.size() == func_exp.size());
    REQUIRE(compare_vectors(func_sample, func_exp));
}