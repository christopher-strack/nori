#include <gtest/gtest.h>
#include <nori/rectangle.h>


TEST(rectangle, construct) {
    rectangle r(nori::position(10, 20), nori::size(30, 40));

    ASSERT_EQ(r.left, 10);
    ASSERT_EQ(r.top, 20);
    ASSERT_EQ(r.right, 40);
    ASSERT_EQ(r.bottom, 60);
}
