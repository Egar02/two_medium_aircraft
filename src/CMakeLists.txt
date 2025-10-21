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