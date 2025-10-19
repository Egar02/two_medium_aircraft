#include <iostream>
#include <vector>
#include <fstream>
#include "Atmosphere.hpp"
#include "utils.hpp"
#include <nlohmann/json.hpp>
#include <unordered_map>
#include "alglib-cpp/integration.h"
#include "alglib-cpp/diffequations.h"
#include "libs/matplotlib-cpp/matplotlibcpp.h"

using json = nlohmann::json;

int main()
{
    std::vector<double> heights;

    read_array_from_file("input.txt", heights);

    std::vector<double> geopotential_heights;

    map(geopotential_height, heights, geopotential_heights);

    json data;

    read_json("./data/density.json", data);

    std::unordered_map<double, double> densities;

    for (const auto& item : data)
    {
        densities[item["height"]] = item["rho"];
    }

    return 0;
}