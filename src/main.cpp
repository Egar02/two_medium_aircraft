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

    // Вычисление молярных масс
    std::vector<double> molar_masses;

    apply_func(molar_mass, heights, molar_masses);

    Gnuplot plt_molar_masses{};
    plt_molar_masses.redirect_to_png("../plots/M-h.png", "800,600");
    plt_molar_masses.plot(heights, molar_masses);
    plt_molar_masses.set_title("График молярной массы от высоты");
    plt_molar_masses.set_xlabel("h, м");
    plt_molar_masses.set_ylabel("M, кг/моль");
    plt_molar_masses.show();
    //________________________________________________________________
    //
    // Вычисление геопотенциальной высоты
    std::vector<double> geopotential_heights;

    apply_func(geopotential_height, heights, geopotential_heights);
    //________________________________________________________________
    //
    // Вычисление молярной температуры
    std::vector<double> molar_temperatures;

    apply_func(molar_temperature, geopotential_heights, molar_temperatures);

    Gnuplot plt_molar_temperatures{};
    plt_molar_temperatures.redirect_to_png("../plots/T_M-h.png", "800,600");
    plt_molar_temperatures.plot(geopotential_heights, molar_temperatures);
    plt_molar_temperatures.set_title("График молярной температуры от высоты");
    plt_molar_temperatures.set_xlabel("h, м");
    plt_molar_temperatures.set_ylabel("T_M, К");
    plt_molar_temperatures.show();
    //________________________________________________________________
    //
    // Вычисление давления
    std::vector<double> pressures;

    apply_func(pressure, geopotential_heights, pressures);

    Gnuplot plt_pressures{};
    plt_pressures.redirect_to_png("../plots/p-h.png", "800,600");
    plt_pressures.plot(geopotential_heights, pressures);
    plt_pressures.set_title("График давления от высоты");
    plt_pressures.set_xlabel("h, м");
    plt_pressures.set_ylabel("p, Па");
    plt_pressures.show();
    //________________________________________________________________
    //
    // Вычисление плотности
    std::vector<double> densities;

    apply_func_2_args(density, pressures, molar_temperatures, densities);

    Gnuplot plt_densities{};
    plt_densities.redirect_to_png("../plots/rho-h.png", "800,600");
    plt_densities.plot(geopotential_heights, densities);
    plt_densities.set_title("График плотности от высоты");
    plt_densities.set_xlabel("h, м");
    plt_densities.set_ylabel("{/Symbol r}, кг/м^3");
    plt_densities.show();

    return 0;
}