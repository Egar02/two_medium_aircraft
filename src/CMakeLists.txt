# Создаем библиотеку
add_library(atmosphere 
    Atmosphere.cpp
    Atmosphere.hpp
)

find_package(nlohmann_json REQUIRED)

# Указываем include директории
target_include_directories(atmosphere 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(atmosphere PRIVATE nlohmann_json::nlohmann_json)

# # Создаем библиотеку
# add_library(utils 
#     utils.cpp
#     utils.hpp
# )

# target_link_libraries(utils PRIVATE nlohmann_json::nlohmann_json)

# # Указываем include директории
# target_include_directories(utils 
#     PUBLIC 
#     ${CMAKE_CURRENT_SOURCE_DIR}
# )