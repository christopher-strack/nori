cmake_minimum_required(VERSION 2.8)

project(nori)


# Options
option(NORI_BUILD_TESTS "Build nori tests" ON)
option(NORI_BUILD_SAMPLES "Build nori samples" ON)


# nori library
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/" ${CMAKE_MODULE_PATH})

find_package(OpenGl REQUIRED)
set(GLEW_ROOT CACHE PATH "Path to GLEW")
find_package(Glew REQUIRED)

include_directories(inc ${GLEW_INCLUDE_DIRS})

file(GLOB nori_sources src/*.cpp)
file(GLOB nori_includes inc/nori/*.h)
add_library(nori ${nori_sources} ${nori_includes})
target_link_libraries(nori ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})


# nori tests
if (NORI_BUILD_TESTS)
    add_subdirectory(tests)
endif()


# nori samples
if (NORI_BUILD_SAMPLES)
    add_subdirectory(samples)
endif()
