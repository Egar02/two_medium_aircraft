# Создаем библиотеку
add_library(atmosphere 
    Atmosphere.cpp
    Atmosphere.hpp
)

# Указываем include директории
target_include_directories(atmosphere 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Создаем библиотеку
add_library(utils 
    utils.cpp
    utils.hpp
)

target_link_libraries(utils PRIVATE nlohmann_json::nlohmann_json)

# Указываем include директории
target_include_directories(utils 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)