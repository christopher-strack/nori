#include "precompiled.h"
#include <gmock/gmock.h>
#include <nori/slicer.h>


TEST(default_slicer, slice) {
    auto slicer = nori::default_slicer();
    auto slices = slicer.slice(nori::size(10, 20));
    ASSERT_EQ(slices.size(), 1);
    ASSERT_EQ(slices.back(), nori::rectangle(0, 0, 10, 20));
}

TEST(grid_slicer, slice) {
    auto slicer = nori::grid_slicer(5, 5);
    auto slices = slicer.slice(nori::size(10, 10));
    ASSERT_EQ(slices.size(), 4);
    ASSERT_EQ(slices[0], nori::rectangle(0, 0, 5, 5));
    ASSERT_EQ(slices[1], nori::rectangle(5, 0, 10, 5));
    ASSERT_EQ(slices[2], nori::rectangle(0, 5, 5, 10));
    ASSERT_EQ(slices[3], nori::rectangle(5, 5, 10, 10));
}

TEST(grid_slicer, slice_too_big_area_drops_rest) {
    auto slicer = nori::grid_slicer(5, 5);
    auto slices = slicer.slice(nori::size(12, 13));
    ASSERT_EQ(slices.size(), 4);
    ASSERT_EQ(slices[0], nori::rectangle(0, 0, 5, 5));
    ASSERT_EQ(slices[1], nori::rectangle(5, 0, 10, 5));
    ASSERT_EQ(slices[2], nori::rectangle(0, 5, 5, 10));
    ASSERT_EQ(slices[3], nori::rectangle(5, 5, 10, 10));
}
