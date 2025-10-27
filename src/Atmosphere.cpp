#include "Atmosphere.hpp"

double R = 8.31432;           // Универсальная газовая постоянная, Дж / (К * моль)
double k = 1.4;               // Показатель адиабаты воздуха, б/р
double S = 110.4;             // Первый коэффициент Сатерленда, К
double BETA_S = 1.458e-6;     // Первый коэффициент Сатерленда, кг / (с * м * К ^ 0.5)
double R_EARTH = 6356.767e+3; // Радиус Земли, м
double M_0 = 28.96442e-3;     // Молярная масса воздуха на высоте 0 м, кг/моль

std::map<double, std::map<std::string, double>> MOLAR_MASS_DATA;
std::map<double, std::map<std::string, double>> MOLAR_TEMPERATURE_DATA;
std::map<double, std::map<std::string, double>> PRESSURE_DATA;
std::array<bool, 12> IS_ISOTERMIC_LAYER{false};

double molar_mass(double height)
{
    if (MOLAR_MASS_DATA.empty())
    {
        nlohmann::json json_file;
        read_json("./data/molar_mass.json", json_file);

        for (const auto &item : json_file)
        {
            double height = item["height"];

            MOLAR_MASS_DATA[height * 1000] = {{"molar_mass", double(item["molar_mass"]) / 1000}, {"gamma", item["gamma"]}};
        }
    }

    auto it = find_lower_bound(height, MOLAR_MASS_DATA);

    double height_ref = it->first;
    double molar_mass_ref = it->second.at("molar_mass");
    double gamma = it->second.at("gamma");

    return molar_mass_ref + gamma * (height - height_ref);
}

double geopotential_height(double height)
{
    return R_EARTH * height / (R_EARTH + height);
}

double molar_temperature(double height)
{
    if (MOLAR_TEMPERATURE_DATA.empty())
    {
        nlohmann::json json_file;
        read_json("./data/molar_temperature.json", json_file);

        for (const auto &item : json_file)
        {
            MOLAR_TEMPERATURE_DATA[item["height"]] = {{"T", item["T"]}, {"alpha", item["alpha"]}};
        }
    }

    auto it = find_lower_bound(height, MOLAR_TEMPERATURE_DATA);

    double height_ref = it->first;
    double T_ref = it->second.at("T");
    double alpha = it->second.at("alpha");

    return T_ref + alpha * (height - height_ref) * 1e+3;
}

double pressure(double height)
{
    if (PRESSURE_DATA.empty())
    {
        nlohmann::json json_file;
        read_json("./data/pressure.json", json_file);

        for (const auto &item : json_file)
        {
            PRESSURE_DATA[item["height"]] = {{"p", item["p"]}, {"beta", item["beta"]}};
        }

        IS_ISOTERMIC_LAYER[2] = true;
        IS_ISOTERMIC_LAYER[5] = true;
        IS_ISOTERMIC_LAYER[8] = true;
    }

    auto pressure_it = find_lower_bound(height, PRESSURE_DATA);
    auto cur_it = PRESSURE_DATA.begin();
    int pos = 0;

    while (cur_it != pressure_it)
    {
        cur_it++;
        pos++;
    }

    if (IS_ISOTERMIC_LAYER[pos])
    {
        return isotermic_pressure(height, pressure_it);
    }

    auto T_it = find_lower_bound(height, MOLAR_TEMPERATURE_DATA);

    return non_isotermic_pressure(height, pressure_it, T_it);
}

double non_isotermic_pressure(double height, std::map<double, std::map<std::string, double>>::const_iterator &pressure_it, std::map<double, std::map<std::string, double>>::const_iterator &T_it)
{
    double p_ref = pressure_it->second.at("p");
    double beta = pressure_it->second.at("beta");

    double T_M_ref = T_it->second.at("T");
    double T_M = molar_temperature(height);

    return p_ref * std::pow(T_M_ref / T_M, beta);
}

double isotermic_pressure(double height, std::map<double, std::map<std::string, double>>::const_iterator &pressure_it)
{
    double height_ref = pressure_it->first;
    double p_ref = pressure_it->second.at("p");
    double beta = pressure_it->second.at("beta");

    return p_ref * std::exp(-beta * (height - height_ref) * 1e+3);
}

double density(double pressure, double T_M)
{
    return pressure * M_0 / (R * T_M);
}

double thermodynamic_temperature(double molar_mass, double T_M)
{
    return molar_mass * T_M / M_0;
}

double sound_speed(double pressure, double density)
{
    return std::sqrt(k * pressure / density);
}

double dynamic_viscosity(double temperature)
{
    return BETA_S * std::pow(temperature, 1.5) / (temperature + S);
}

double kinematic_viscosity(double dynamic_viscosity, double density)
{
    return dynamic_viscosity / density;
}
