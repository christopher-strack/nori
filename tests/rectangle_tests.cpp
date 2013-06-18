#include "precompiled.h"
#include <gtest/gtest.h>
#include <nori/rectangle.h>


TEST(rectangle, construct_default) {
    nori::rectangle r;
    ASSERT_EQ(r.left, 0);
    ASSERT_EQ(r.top, 0);
    ASSERT_EQ(r.right, 0);
    ASSERT_EQ(r.bottom, 0);
}

TEST(rectangle, construct) {
    nori::rectangle r(1, 2, 3, 4);
    ASSERT_EQ(r.left, 1);
    ASSERT_EQ(r.top, 2);
    ASSERT_EQ(r.right, 3);
    ASSERT_EQ(r.bottom, 4);
}

TEST(rectangle, construct_by_size_and_position) {
    nori::rectangle r(nori::point(10, 20), nori::size(30, 40));
    ASSERT_EQ(r.left, 10);
    ASSERT_EQ(r.top, 20);
    ASSERT_EQ(r.right, 40);
    ASSERT_EQ(r.bottom, 60);
}

TEST(rectangle, compare) {
    nori::rectangle r1(nori::point(10, 20), nori::size(30, 40));
    nori::rectangle r2(nori::point(10, 20), nori::size(30, 40));
    nori::rectangle r3(nori::point(50, 60), nori::size(70, 80));
    ASSERT_EQ(r1, r2);
    ASSERT_NE(r1, r3);
}

TEST(rectangle, position) {
    nori::rectangle r(nori::point(10, 20), nori::size(30, 40));
    ASSERT_EQ(r.position(), nori::point(10, 20));
}

TEST(rectangle, size) {
    nori::rectangle r(nori::point(10, 20), nori::size(30, 40));
    ASSERT_EQ(r.size(), nori::size(30, 40));
}

TEST(rectangle, cast) {
    nori::rectangle_t<int> r1;
    nori::rectangle_t<float> r2 = r1;
}

TEST(rectangle, inside_true_if_equal) {
    nori::rectangle r1(nori::point(10, 20), nori::size(30, 40));
    nori::rectangle r2(nori::point(10, 20), nori::size(30, 40));
    ASSERT_TRUE(r1.inside(r2));
}

TEST(rectangle, inside_false_if_intersecting) {
    nori::rectangle r(nori::point(10, 20), nori::size(30, 40));
    ASSERT_FALSE(nori::rectangle(nori::point(9, 20), nori::size(30, 40)).inside(r));
    ASSERT_FALSE(nori::rectangle(nori::point(10, 19), nori::size(30, 40)).inside(r));
    ASSERT_FALSE(nori::rectangle(nori::point(10, 20), nori::size(31, 40)).inside(r));
    ASSERT_FALSE(nori::rectangle(nori::point(10, 20), nori::size(30, 41)).inside(r));
}

TEST(rectangle, inside_false_if_outside) {
    nori::rectangle r(nori::point(10, 20), nori::size(30, 40));
    ASSERT_FALSE(nori::rectangle(nori::point(0, 20), nori::size(10, 40)).inside(r));
    ASSERT_FALSE(nori::rectangle(nori::point(10, 0), nori::size(30, 20)).inside(r));
    ASSERT_FALSE(nori::rectangle(nori::point(40, 20), nori::size(5, 40)).inside(r));
    ASSERT_FALSE(nori::rectangle(nori::point(10, 60), nori::size(30, 5)).inside(r));
}
