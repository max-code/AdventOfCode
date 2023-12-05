
cmake_minimum_required (VERSION 3.8)

project ("AdventOfCode/2023")

foreach(day RANGE 0 25)
    set(day_name "day${day}")

    # Add executable for each day
    add_executable(${day_name} "${day_name}/${day_name}.cpp" "util/util.h" "util/util.cpp")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")

    # set(CMAKE_CXX_FLAGS_RELEASE "-O3")

    if (CMAKE_VERSION VERSION_GREATER 3.12)
        set_property(TARGET ${day_name} PROPERTY CXX_STANDARD 20)
    endif()
endforeach()

