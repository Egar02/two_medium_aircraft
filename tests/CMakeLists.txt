cmake_minimum_required(VERSION 3.10)
project(MyProjectWithTests)

# Добавляем исполняемый файл с тестами
add_executable(tests
    test_utils.cpp
    test_Atmosphere.cpp
)

target_link_libraries(tests
    PRIVATE
    atmosphere
    Catch2::Catch2WithMain
)

add_test(
    NAME test_Atmosphere
    COMMAND tests
)