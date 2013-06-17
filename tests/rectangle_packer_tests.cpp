#include <gtest/gtest.h>
#include <nori/detail/rectangle_packer.h>


TEST(rectangle_packer, construct) {
    nori::detail::rectangle_packer packer(nori::size(20, 20));
}

TEST(rectangle_packer, pack_whole_region) {
    nori::rectangle rect;
    nori::detail::rectangle_packer packer(nori::size(20, 20));
    bool result = packer.pack(nori::size(20, 20), rect);
    ASSERT_TRUE(result);
    ASSERT_EQ(rect, nori::rectangle(0, 0, 20, 20));
}

TEST(rectangle_packer, pack_1d_fails) {
    nori::rectangle rect;
    nori::detail::rectangle_packer packer(nori::size(20, 20));
    ASSERT_FALSE(packer.pack(nori::size(20, 0), rect));
    ASSERT_FALSE(packer.pack(nori::size(0, 20), rect));
}

TEST(rectangle_packer, pack_full_packer_fails) {
    nori::rectangle rect;
    nori::detail::rectangle_packer packer(nori::size(20, 20));
    packer.pack(nori::size(20, 20), rect);
    ASSERT_FALSE(packer.pack(nori::size(1, 1), rect));
}

TEST(rectangle_packer, pack_left_to_right) {
    nori::rectangle rect;
    nori::detail::rectangle_packer packer(nori::size(20, 20));
    ASSERT_TRUE(packer.pack(nori::size(10, 10), rect));
    ASSERT_EQ(rect, nori::rectangle(0, 0, 10, 10));
    ASSERT_TRUE(packer.pack(nori::size(10, 10), rect));
    ASSERT_EQ(rect, nori::rectangle(10, 0, 20, 10));
    ASSERT_TRUE(packer.pack(nori::size(10, 10), rect));
    ASSERT_EQ(rect, nori::rectangle(0, 10, 10, 20));
    ASSERT_TRUE(packer.pack(nori::size(10, 10), rect));
    ASSERT_EQ(rect, nori::rectangle(10, 10, 20, 20));
    ASSERT_FALSE(packer.pack(nori::size(1, 1), rect));
}
