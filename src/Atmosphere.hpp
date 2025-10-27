#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <string>
#include <iterator>
#include "utils.hpp"

double molar_mass(double height);

double geopotential_height(double height);

double molar_temperature(double height);

double pressure(double height);

double non_isotermic_pressure(double height, std::map<double, std::map<std::string, double>>::const_iterator &pressure_it, std::map<double, std::map<std::string, double>>::const_iterator &T_it);

double isotermic_pressure(double height, std::map<double, std::map<std::string, double>>::const_iterator &pressure_it);
