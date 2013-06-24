#include "precompiled.h"
#include <gmock/gmock.h>
#include <nori/vector2.h>


TEST(vector2, construct) {
    nori::vector2<int> v;
    ASSERT_EQ(v.x, 0);
    ASSERT_EQ(v.y, 0);
}

TEST(vector2, assign_construct) {
    nori::vector2<int> v(10, 15);
    ASSERT_EQ(v.x, 10);
    ASSERT_EQ(v.y, 15);
}

TEST(vector2, copy_construct) {
    nori::vector2<int> v1(10, 15);
    nori::vector2<int> v2(v1);
    ASSERT_EQ(v2.x, v1.x);
    ASSERT_EQ(v2.y, v1.y);
}

TEST(vector2, copy_assign) {
    nori::vector2<int> v1(10, 15);
    nori::vector2<int> v2;
    v2 = v1;
    ASSERT_EQ(v2.x, v1.x);
    ASSERT_EQ(v2.y, v1.y);
}

TEST(vector2, compare) {
    nori::vector2<int> v1(10, 15);
    nori::vector2<int> v2(15, 10);
    nori::vector2<int> v3(15, 10);
    ASSERT_TRUE(v1 != v2);
    ASSERT_TRUE(v2 == v3);
}

TEST(vector2, cast) {
    nori::vector2<int> v1;
    nori::vector2<float> v2 = v1;
}

TEST(vector2, multiply) {
    nori::vector2<float> v(10, 20);
    ASSERT_EQ(v * 0.5f, nori::vector2<float>(5, 10));
}

TEST(vector2, divide) {
    nori::vector2<float> v(10, 20);
    ASSERT_EQ(v / 2.0f, nori::vector2<float>(5, 10));
}
