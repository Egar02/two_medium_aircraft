#include <iostream>
#include <vector>
#include <fstream>
#include "Atmosphere.hpp"
#include "utils.hpp"
#include <nlohmann/json.hpp>
#include <unordered_map>
#include "alglib-cpp/integration.h"
#include "alglib-cpp/diffequations.h"
#include "libs/gplot++/gplot++.h"

using json = nlohmann::json;

int main()
{
    std::vector<double> heights;

    read_array_from_file("input.txt", heights);

    std::vector<double> geopotential_heights;

    apply_func(geopotential_height, heights, geopotential_heights);

    std::vector<double> molar_masses;

    apply_func(molar_mass, heights, molar_masses);

    Gnuplot plt{};

    return 0;
}