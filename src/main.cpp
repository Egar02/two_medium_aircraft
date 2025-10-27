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

    json data;

    read_json("./data/density.json", data);

    std::unordered_map<double, double> densities;

    std::vector<double> plot_heights, plot_densities;

    for (const auto &item : data)
    {
        densities[item["height"]] = item["rho"];
        plot_heights.push_back(item["height"]);
        plot_densities.push_back(item["rho"]);
    }

    Gnuplot plt{};

    plt.redirect_to_png("../plots/h-rho.png", "800,600");
    plt.plot(plot_heights, plot_densities, "h-rho");
    plt.show();

    molar_mass(20.0);
    molar_mass(100.0);
    molar_mass(400.0);

    molar_temperature(47.0);
    molar_temperature(48.0);
    molar_temperature(400.0);

    std::cout << pressure(0) << std::endl;
    std::cout << pressure(15) << std::endl;
    std::cout << pressure(48) << std::endl;
    std::cout << pressure(90) << std::endl;
    std::cout << pressure(30) << std::endl;
    std::cout << pressure(400) << std::endl;

    double p_0 = pressure(0);
    double T_M = molar_temperature(0);

    double rho_0 = density(p_0, T_M);

    return 0;
}