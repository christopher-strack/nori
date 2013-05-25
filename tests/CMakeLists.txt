set(GTEST_ROOT CACHE PATH "Path to gtest")

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB nori_test_sources *.cpp)
add_executable(nori_tests ${nori_test_sources})

target_link_libraries(nori_tests nori ${GTEST_BOTH_LIBRARIES})
