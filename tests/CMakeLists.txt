set(GTEST_ROOT CACHE PATH "Path to gtest")

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(nori_tests application_test.cpp)

target_link_libraries(nori_tests nori ${GTEST_BOTH_LIBRARIES})
