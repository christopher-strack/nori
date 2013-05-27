cmake_minimum_required(VERSION 2.8)

project(nori)


# Options
option(NORI_BUILD_TESTS "Build nori tests" ON)
option(NORI_BUILD_SAMPLES "Build nori samples" ON)


# nori library
if (WIN32)
    set(nori_platform_folder "windows")
elseif(ANDROID)
    set(nori_platform_folder "android")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/" ${CMAKE_MODULE_PATH})

if (WIN32)
    find_package(OpenGl REQUIRED)
    set(GLEW_ROOT CACHE PATH "Path to GLEW")
    find_package(Glew REQUIRED)
endif()

set(BOOST_ROOT CACHE PATH "Path to boost")
find_package(Boost REQUIRED)

include_directories(inc ${GLEW_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

file(GLOB nori_sources src/*.cpp src/${nori_platform_folder}/*.cpp)
file(GLOB nori_includes inc/nori/*.h inc/nori/detail/*.h)
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
