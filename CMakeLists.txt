cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)

set(BUILD_SHARED_LIBS OFF)
add_subdirectory(lib/hidapi)

project(catz_settings LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_executable(catz_settings_demo demo.cpp)
target_link_libraries(catz_settings_demo PRIVATE hidapi::hidapi)

add_executable(catz_settings
    main.cpp
    ui/CatzSettingsUi.cpp
)
target_link_libraries(catz_settings PRIVATE ${wxWidgets_LIBRARIES})
