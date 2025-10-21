cmake_minimum_required(VERSION 3.10)
project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src)

include(FetchContent)

enable_testing()

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

# # Либа Catch2
# Настраиваем загрузку Catch2
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.11.0  # Укажите нужную версию
)

# Загружаем и делаем доступной Catch2
FetchContent_MakeAvailable(Catch2)

# Добавляем исполняемый файл
add_executable(program ./src/main.cpp ./src/utils.cpp ./src/Atmosphere.cpp)

# Связываем с библиотеками
target_link_libraries(program PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(program PRIVATE alglib-cpp)

set_target_properties(program PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )

add_subdirectory(src)
add_subdirectory(tests)
