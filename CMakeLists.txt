cmake_minimum_required(VERSION 3.10)
project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src)

include(FetchContent)

# # Либа nlohmann::json
#
# Загружаем либу из репозитория
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.12.0  # Указываем конкретную версию
)

FetchContent_MakeAvailable(nlohmann_json)
#
# #

# # Либа alglib-cpp
#
# Добавляем alglib-cpp как статическую библиотеку
add_library(alglib-cpp STATIC
    src/libs/alglib-cpp/src/alglibinternal.cpp
    src/libs/alglib-cpp/src/alglibmisc.cpp
    src/libs/alglib-cpp/src/ap.cpp
    src/libs/alglib-cpp/src/dataanalysis.cpp
    src/libs/alglib-cpp/src/diffequations.cpp
    src/libs/alglib-cpp/src/fasttransforms.cpp
    src/libs/alglib-cpp/src/integration.cpp
    src/libs/alglib-cpp/src/interpolation.cpp
    src/libs/alglib-cpp/src/kernels_avx2.cpp
    src/libs/alglib-cpp/src/kernels_fma.cpp
    src/libs/alglib-cpp/src/kernels_sse2.cpp
    src/libs/alglib-cpp/src/linalg.cpp
    src/libs/alglib-cpp/src/minlp.cpp
    src/libs/alglib-cpp/src/optimization.cpp
    src/libs/alglib-cpp/src/solvers.cpp
    src/libs/alglib-cpp/src/specialfunctions.cpp
    src/libs/alglib-cpp/src/statistics.cpp
)
# Указываем include директории для ALGLIB
target_include_directories(alglib-cpp PUBLIC 
    src/libs/alglib-cpp/include/
)
#
# #

# # Либа matplotlib-cpp
#
# Поиск Python (обязательно)
find_package(Python REQUIRED COMPONENTS Interpreter Development)
# Настройка matplotlib-cpp
FetchContent_Declare(
    matplotlib-cpp
    GIT_REPOSITORY https://github.com/lava/matplotlib-cpp.git
    GIT_TAG master
)
FetchContent_MakeAvailable(matplotlib-cpp)
#
# #

# Добавляем исполняемый файл
add_executable(program ./src/main.cpp ./src/utils.cpp ./src/Atmosphere.cpp)

# Связываем с библиотеками
target_link_libraries(program PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(program PRIVATE alglib-cpp)
target_link_libraries(program PRIVATE matplotlib_cpp Python::Python
)

set_target_properties(program PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )

# Добавляем пути к заголовочным файлам Python
target_include_directories(program 
    PRIVATE 
    ${Python_INCLUDE_DIRS}
)