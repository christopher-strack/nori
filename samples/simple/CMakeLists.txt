project(simple_sample)

if (ANDROID)
    set(LIBRARY_OUTPUT_PATH "${simple_sample_SOURCE_DIR}/libs/${ANDROID_NDK_ABI_NAME}")
endif()

if (ANDROID)
    add_library(simple_sample SHARED simple.cpp)
else()
    add_executable(simple_sample simple.cpp)
endif()

target_link_libraries(simple_sample nori)
