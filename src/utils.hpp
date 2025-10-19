#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <vector>
#include <nlohmann/json.hpp>

void read_array_from_file(std::string&& file_path, std::vector<double>& array);

void read_json(std::string&& file_path, nlohmann::json& json_data);

void map(std::function<double(double)> func, std::vector<double>& array, std::vector<double>& mapped_array);