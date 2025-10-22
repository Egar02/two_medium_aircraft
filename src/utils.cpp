#include "utils.hpp"

void read_array_from_file(std::string &&file_path, std::vector<double> &array)
{
    std::ifstream input_file;

    input_file.open(file_path);

    if (!input_file.is_open()) 
    {
        std::cerr << "Не удалось открыть файл!" << std::endl;

        if (errno == ENOENT) 
        {
            std::filesystem::path current_path = std::filesystem::current_path();
            std::cerr << "Файл не существует" << std::endl;
            std::cout << "Текущая директория: " << current_path << std::endl;

        } else if (errno == EACCES) {
            std::cerr << "Нет прав доступа" << std::endl;
        }

        return;
    }

    double number;

    while (input_file >> number)
    {
        array.push_back(number);
    }

    input_file.close();
}

void read_json(std::string &&file_path, nlohmann::json &json_data)
{
    if (!std::filesystem::exists(file_path))
    {
        std::filesystem::path current_path = std::filesystem::current_path();
        std::cerr << "Файл не существует" << std::endl;
        std::cout << "Текущая директория: " << current_path << std::endl;
    }

    std::ifstream json_file(file_path);

    json_data = nlohmann::json::parse(json_file);

    json_file.close();
}

void apply_func(std::function<double(double)> func, std::vector<double> &array, std::vector<double> &mapped_array)
{
    for (double element : array)
    {
        mapped_array.push_back(func(element));
    }
}