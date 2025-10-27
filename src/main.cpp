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

    Gnuplot plt_molar_masses{};
    plt_molar_masses.redirect_to_png("../plots/M-h.png", "800,600");
    plt_molar_masses.plot(heights, molar_masses);
    plt_molar_masses.set_title("График молярной массы от высоты");
    plt_molar_masses.set_xlabel("h, м");
    plt_molar_masses.set_ylabel("M, кг/моль");
    plt_molar_masses.show();

    return 0;
}