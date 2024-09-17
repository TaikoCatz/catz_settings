cmake_minimum_required(VERSION 3.28)

add_subdirectory(lib/hidapi)

project(catz_settings)
set(CMAKE_CXX_STANDARD 20)

add_executable(catz_settings_demo demo.cpp)
target_link_libraries(catz_settings_demo hidapi::hidapi)
