#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <vector>

void read_array_from_file(std::string&& file_path, std::vector<double>& array);

void map(std::function<double(double)> func, std::vector<double>& array, std::vector<double>& mapped_array);