cmake_minimum_required(VERSION 3.10)
project(MyProjectWithTests)

# Добавляем исполняемый файл с тестами
add_executable(tests
    test_utils.cpp
    test_Atmosphere.cpp
)

# Связываем с Catch2
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)