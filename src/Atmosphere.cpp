#include "Atmosphere.hpp"

double R = 8.31432;           // Универсальная газовая постоянная, Дж / (К * моль)
double k = 1.4;               // Показатель адиабаты воздуха, б/р
double S = 110.4;             // Первый коэффициент Сатерленда, К
double beta_S = 1.458e-6;     // Первый коэффициент Сатерленда, кг / (с * м * К ^ 0.5)
double R_EARTH = 6356.767e+3; // Радиус Земли, м

std::map<double, std::map<std::string, double>> MOLAR_MASS_DATA;

double molar_mass(double height)
{
    if (MOLAR_MASS_DATA.empty())
    {
        nlohmann::json json_file;
        read_json("./data/molar_mass.json", json_file);

        for (const auto &item : json_file)
        {
            MOLAR_MASS_DATA[item["height"]] = {{"molar_mass", item["molar_mass"]}, {"gamma", item["gamma"]}};
        }
    }

    return 0.0;
}

double geopotential_height(double height)
{
    return R_EARTH * height / (R_EARTH + height);
}
