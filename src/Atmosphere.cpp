#include "Atmosphere.hpp"

double R = 8.31432; // Универсальная газовая постоянная, Дж / (К * моль)
double k = 1.4; // Показатель адиабаты воздуха, б/р
double S = 110.4; // Первый коэффициент Сатерленда, К
double beta_S = 1.458e-6; // Первый коэффициент Сатерленда, кг / (с * м * К ^ 0.5)
double R_EARTH = 6356.767e+3; // Радиус Земли, м

double geopotential_height(double height)
{
    return R_EARTH * height / (R_EARTH + height);
}
