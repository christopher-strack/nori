cmake_minimum_required(VERSION 2.8)

project(nori)


# Options
option(NORI_BUILD_TESTS "Build nori tests" ON)
option(NORI_BUILD_SAMPLES "Build nori samples" ON)

include("cmake/precompiled_header.cmake")


# nori library
if (WIN32)
    set(nori_platform_folder "windows")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4355 /wd4996")
elseif (ANDROID)
    set(ANDROID_NATIVE_API_LEVEL 14)
    set(nori_platform_folder "android")

    include_directories("${ANDROID_NDK}/platforms/android-${ANDROID_NATIVE_API_LEVEL}/arch-${ANDROID_ARCH_NAME}/usr/include")
    link_directories("${ANDROID_NDK}/platforms/android-${ANDROID_NATIVE_API_LEVEL}/arch-${ANDROID_ARCH_NAME}/usr/lib")

    set(native_app_glue_sources
        "${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c")
    add_library(native_app_glue STATIC ${native_app_glue_sources})
    target_link_libraries(native_app_glue android)

    set(Android_LIBRARIES native_app_glue android log EGL GLESv2)
    set(Android_INCLUDE_DIRS "${ANDROID_NDK}/sources/android/native_app_glue")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/" ${CMAKE_MODULE_PATH})

if (WIN32)
    find_package(OpenGl REQUIRED)
    set(GLEW_ROOT CACHE PATH "Path to GLEW")
    find_package(Glew REQUIRED)

    add_definitions(/D_SCL_SECURE_NO_WARNINGS)
endif()

set(BOOST_ROOT CACHE PATH "Path to boost")
find_package(Boost REQUIRED)

include_directories(
    include
    ${GLEW_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${Android_INCLUDE_DIRS})

file(GLOB nori_sources src/*.cpp src/${nori_platform_folder}/*.cpp)
file(GLOB nori_includes include/nori/*.h include/nori/detail/*.h)

add_precompiled_header(
    "nori/detail/precompiled.h"
    src/precompiled.cpp
    "${nori_sources}")

add_library(nori ${nori_sources} ${nori_includes})
target_link_libraries(nori ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${Android_LIBRARIES})


# nori tests
if (NORI_BUILD_TESTS)
    add_subdirectory(tests)
endif()


# nori samples
if (NORI_BUILD_SAMPLES)
    add_subdirectory(samples/simple)
    add_subdirectory(samples/basic_drawing)
endif()
