
cmake_minimum_required (VERSION 3.8)

project ("AdventOfCode/2023")

foreach(day RANGE 0 2)
    set(day_name "day${day}")

    # Add executable for each day
    add_executable(${day_name} "${day_name}/${day_name}.cpp" "util/util.h" "util/util.cpp")
    if(MSVC)
        # Set optimization flags
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /O2")
        # Other flags like /Ob2 for inline function expansion can be added here
    endif()

    if (CMAKE_VERSION VERSION_GREATER 3.12)
        set_property(TARGET ${day_name} PROPERTY CXX_STANDARD 20)
    endif()
endforeach()

