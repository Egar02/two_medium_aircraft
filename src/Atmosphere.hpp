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

double density(double pressure, double T_M);

double thermodynamic_temperature(double molar_mass, double T_M);

double sound_speed(double pressure, double density);

double dynamic_viscosity(double temperature);

double kinematic_viscosity(double dynamic_viscosity, double density);