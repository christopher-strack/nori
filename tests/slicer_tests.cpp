#include "precompiled.h"
#include <gmock/gmock.h>
#include <nori/slicer.h>

#include <boost/assign.hpp>


TEST(default_slicer, slice) {
    nori::default_slicer slicer;
    auto slices = slicer.slice(nori::size(10, 20));
    ASSERT_EQ(slices.size(), 1);
    ASSERT_EQ(slices.back(), nori::rectangle(0, 0, 10, 20));
}


TEST(grid_slicer, slice) {
    nori::grid_slicer slicer(5, 5);
    auto slices = slicer.slice(nori::size(10, 10));
    ASSERT_EQ(slices.size(), 4);
    ASSERT_EQ(slices[0], nori::rectangle(0, 0, 5, 5));
    ASSERT_EQ(slices[1], nori::rectangle(5, 0, 10, 5));
    ASSERT_EQ(slices[2], nori::rectangle(0, 5, 5, 10));
    ASSERT_EQ(slices[3], nori::rectangle(5, 5, 10, 10));
}

TEST(grid_slicer, slice_too_big_area_drops_rest) {
    nori::grid_slicer slicer(5, 5);
    auto slices = slicer.slice(nori::size(12, 13));
    ASSERT_EQ(slices.size(), 4);
    ASSERT_EQ(slices[0], nori::rectangle(0, 0, 5, 5));
    ASSERT_EQ(slices[1], nori::rectangle(5, 0, 10, 5));
    ASSERT_EQ(slices[2], nori::rectangle(0, 5, 5, 10));
    ASSERT_EQ(slices[3], nori::rectangle(5, 5, 10, 10));
}


TEST(custom_slicer, empty_by_default) {
    nori::custom_slicer slicer;
    auto slices = slicer.slice(nori::size(64, 64));
    ASSERT_EQ(slices.size(), 0);
}

TEST(custom_slicer, return_added_slices) {
    nori::custom_slicer slicer;
    slicer.add_slice(nori::rectangle(0, 0, 10, 20));
    auto slices = slicer.slice(nori::size(64, 64));
    ASSERT_EQ(slices.size(), 1);
    ASSERT_EQ(slices[0], nori::rectangle(0, 0, 10, 20));
}

TEST(custom_slicer, add_multiple_slices) {
    using namespace boost::assign;

    nori::custom_slicer slicer;
    nori::rectangle_list rectangles;
    rectangles += nori::rectangle(0, 0, 10, 20), nori::rectangle(10, 0, 20, 20);
    slicer.add_slices(rectangles);
    auto slices = slicer.slice(nori::size(64, 64));
    ASSERT_EQ(slices, rectangles);
}
