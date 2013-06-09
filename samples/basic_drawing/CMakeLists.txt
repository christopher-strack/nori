project(basic_drawing_sample)

if (ANDROID)
    set(LIBRARY_OUTPUT_PATH "${basic_drawing_sample_SOURCE_DIR}/libs/${ANDROID_NDK_ABI_NAME}")
endif()

if (ANDROID)
    add_library(basic_drawing_sample SHARED basic_drawing.cpp)
else()
    add_executable(basic_drawing_sample basic_drawing.cpp)
endif()

target_link_libraries(basic_drawing_sample nori)
