project(nori_tests)

if (ANDROID)
    set(LIBRARY_OUTPUT_PATH "${nori_tests_SOURCE_DIR}/libs/${ANDROID_NDK_ABI_NAME}")
endif()

set(GTEST_ROOT CACHE PATH "Path to gtest")
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB nori_test_sources *.cpp)

add_precompiled_header(
    "precompiled.h"
    precompiled.cpp
    "${nori_test_sources}")

if (WIN32)
    add_executable(nori_tests ${nori_test_sources})
elseif (ANDROID)
    add_library(nori_tests SHARED ${nori_test_sources})
endif()

target_link_libraries(nori_tests nori ${GTEST_LIBRARIES})
