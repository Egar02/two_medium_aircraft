cmake_minimum_required(VERSION 3.10)
project(MyProjectWithTests)

# Добавляем исполняемый файл с тестами
add_executable(test_atmosphere
    test_Atmosphere.cpp
)

target_link_libraries(test_atmosphere
    PRIVATE
    atmosphere
    Catch2::Catch2WithMain
)

add_executable(test_utils
    test_utils.cpp
)

target_link_libraries(test_utils
    PRIVATE
    utils
    Catch2::Catch2WithMain
    nlohmann_json::nlohmann_json
)

add_test(
    NAME test_atmosphere
    COMMAND test_atmosphere
)

add_test(
    NAME test_utils
    COMMAND test_utils
)