#include <iostream>
#include <vector>
#include <fstream>
#include "Atmosphere.hpp"
#include "utils.hpp"
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <format>
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
    //________________________________________________________________
    //
    // Вычисление термодинамической температуры
    std::vector<double> thermodynamic_temperatures;

    apply_func_2_args(thermodynamic_temperature, molar_masses, molar_temperatures, thermodynamic_temperatures);

    Gnuplot plt_thermodynamic_temperatures{};
    plt_thermodynamic_temperatures.redirect_to_png("../plots/T-h.png", "800,600");
    plt_thermodynamic_temperatures.plot(geopotential_heights, thermodynamic_temperatures);
    plt_thermodynamic_temperatures.set_title("График термодинамической температуры от высоты");
    plt_thermodynamic_temperatures.set_xlabel("h, м");
    plt_thermodynamic_temperatures.set_ylabel("T, К");
    plt_thermodynamic_temperatures.show();
    //________________________________________________________________
    //
    // Вычисление скростей звука
    std::vector<double> sound_speeds;

    apply_func_2_args(sound_speed, pressures, densities, sound_speeds);

    Gnuplot plt_sound_speeds{};
    plt_sound_speeds.redirect_to_png("../plots/a-h.png", "800,600");
    plt_sound_speeds.plot(geopotential_heights, sound_speeds);
    plt_sound_speeds.set_title("График скорости звука от высоты");
    plt_sound_speeds.set_xlabel("h, м");
    plt_sound_speeds.set_ylabel("a, м/с");
    plt_sound_speeds.show();
    //________________________________________________________________
    //
    // Вычисление динамической вязкости
    std::vector<double> dynamic_viscosities;

    apply_func(dynamic_viscosity, thermodynamic_temperatures, dynamic_viscosities);

    Gnuplot plt_dynamic_viscosities{};
    plt_dynamic_viscosities.redirect_to_png("../plots/mu-h.png", "800,600");
    plt_dynamic_viscosities.plot(geopotential_heights, dynamic_viscosities);
    plt_dynamic_viscosities.set_title("График динамической вязкости от высоты");
    plt_dynamic_viscosities.set_xlabel("h, м");
    plt_dynamic_viscosities.set_ylabel("{/Symbol m}, Па*с");
    plt_dynamic_viscosities.show();
    //________________________________________________________________
    //
    // Вычисление кинематической вязкости
    std::vector<double> kinematic_viscosities;

    apply_func_2_args(kinematic_viscosity, dynamic_viscosities, densities, kinematic_viscosities);

    Gnuplot plt_kinematic_viscosities{};
    plt_kinematic_viscosities.redirect_to_png("../plots/nu-h.png", "800,600");
    plt_kinematic_viscosities.plot(geopotential_heights, kinematic_viscosities);
    plt_kinematic_viscosities.set_title("График кинематической вязкости от высоты");
    plt_kinematic_viscosities.set_xlabel("h, м");
    plt_kinematic_viscosities.set_ylabel("{/Symbol n}, м^2/с");
    plt_kinematic_viscosities.show();
    //________________________________________________________________
    //
    // Вывод результатов в файл
    std::ofstream output_file("../results/atmosphere.txt");

    output_file << "h, км\t\th_Г, км\t\tT_M, К\t\tp, Па\t\trho, кг/м^3\t\tT, К\t\ta, м/с\t\tmu, Па*с\t\tnu, м^2/c" << std::endl;

    for (int i = 0; i < heights.size(); ++i)
    {
        output_file << std::format("{:.3f}", heights[i] / 1000) << "\t\t"
                    << std::format("{:.3f}", geopotential_heights[i] / 1000) << "\t\t"
                    << std::format("{:.3f}", molar_temperatures[i]) << "\t\t"
                    << std::format("{:.3f}", pressures[i]) << "\t\t"
                    << std::format("{:.3f}", densities[i]) << "\t\t"
                    << std::format("{:.3f}", thermodynamic_temperatures[i]) << "\t\t"
                    << std::format("{:.3f}", sound_speeds[i]) << "\t\t"
                    << std::format("{:.3e}", dynamic_viscosities[i]) << "\t\t"
                    << std::format("{:.3e}", kinematic_viscosities[i]) << "\n";
    }

    output_file.close();

    return 0;
}