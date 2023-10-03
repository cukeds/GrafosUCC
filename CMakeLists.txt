cmake_minimum_required(VERSION 3.23)
project(grafos)

set(CMAKE_CXX_STANDARD 23)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "./SFML-2.6.0/lib/cmake/SFML")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(grafos main.cpp)
target_link_libraries(grafos sfml-graphics sfml-window sfml-system)