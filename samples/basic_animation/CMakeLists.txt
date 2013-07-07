project(basic_animation_sample)

if (ANDROID)
    set(LIBRARY_OUTPUT_PATH "${basic_animation_sample_SOURCE_DIR}/libs/${ANDROID_NDK_ABI_NAME}")
endif()

if (ANDROID)
    add_library(basic_animation_sample SHARED basic_animation.cpp)
else()
    add_executable(basic_animation_sample basic_animation.cpp)
endif()

target_link_libraries(basic_animation_sample nori)
