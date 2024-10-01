cmake_minimum_required(VERSION 3.28)

set(BUILD_SHARED_LIBS OFF)
add_subdirectory(lib/hidapi)

project(catz_settings LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    set(wxWidgets_CONFIGURATION mswu)
    add_compile_options(/utf-8)
    # Disable exceptions and RTTI
    add_compile_options(/EHs-c-)
    add_compile_options(/GR-)
endif()

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_executable(catz_settings
    main.cpp
    ui/CatzSettingsUi.cpp
)
target_link_libraries(catz_settings PRIVATE ${wxWidgets_LIBRARIES})

if(WIN32)
    target_link_options(catz_settings PRIVATE /SUBSYSTEM:WINDOWS)
endif()
