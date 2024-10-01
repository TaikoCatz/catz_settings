cmake_minimum_required(VERSION 3.28)

set(BUILD_SHARED_LIBS OFF)
add_subdirectory(lib/hidapi)

project(catz_settings LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)

if(WIN32)
    set(wxWidgets_CONFIGURATION mswu)
    add_compile_options(/utf-8)
endif()

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_executable(catz_settings
    dongle.cpp
    main.cpp
    settings.cpp
    ui/CatzSettingsUi.cpp
)
target_link_libraries(catz_settings PRIVATE
    hidapi::hidapi
    ${wxWidgets_LIBRARIES}
)

if(WIN32)
    target_link_options(catz_settings PRIVATE /SUBSYSTEM:WINDOWS)
endif()
