cmake_minimum_required(VERSION 2.8)

project(nori)


# Options
option(NORI_BUILD_TESTS "Build nori tests" ON)
option(NORI_BUILD_SAMPLES "Build nori samples" ON)


# nori library
include_directories(inc)

file(GLOB nori_sources src/*.cpp)
file(GLOB nori_includes inc/nori/*.h)
add_library(nori ${nori_sources} ${nori_includes})


# nori tests
if (NORI_BUILD_TESTS)
    add_subdirectory(tests)
endif()


# nori samples
if (NORI_BUILD_SAMPLES)
    add_subdirectory(samples)
endif()
