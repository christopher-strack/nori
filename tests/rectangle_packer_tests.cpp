#include "precompiled.h"
#include <gmock/gmock.h>
#include <nori/detail/rectangle_packer.h>


TEST(rectangle_packer, construct) {
    nori::detail::rectangle_packer packer(nori::size(20, 20));
}

TEST(rectangle_packer, pack_whole_region) {
    nori::detail::rectangle_packer packer(nori::size(20, 20));
    auto rect = packer.pack(nori::size(20, 20));
    ASSERT_TRUE(rect);
    ASSERT_EQ(*rect, nori::rectangle(0, 0, 20, 20));
}

TEST(rectangle_packer, pack_1d_fails) {
    nori::detail::rectangle_packer packer(nori::size(20, 20));
    ASSERT_FALSE(packer.pack(nori::size(20, 0)));
    ASSERT_FALSE(packer.pack(nori::size(0, 20)));
}

TEST(rectangle_packer, pack_full_packer_fails) {
    nori::detail::rectangle_packer packer(nori::size(20, 20));
    packer.pack(nori::size(20, 20));
    ASSERT_FALSE(packer.pack(nori::size(1, 1)));
}

TEST(rectangle_packer, pack_left_to_right) {
    boost::optional<nori::rectangle> rect;
    nori::detail::rectangle_packer packer(nori::size(20, 20));
    ASSERT_TRUE(rect = packer.pack(nori::size(10, 10)));
    ASSERT_EQ(*rect, nori::rectangle(0, 0, 10, 10));
    ASSERT_TRUE(rect = packer.pack(nori::size(10, 10)));
    ASSERT_EQ(*rect, nori::rectangle(10, 0, 20, 10));
    ASSERT_TRUE(rect = packer.pack(nori::size(10, 10)));
    ASSERT_EQ(*rect, nori::rectangle(0, 10, 10, 20));
    ASSERT_TRUE(rect = packer.pack(nori::size(10, 10)));
    ASSERT_EQ(*rect, nori::rectangle(10, 10, 20, 20));
    ASSERT_FALSE(packer.pack(nori::size(1, 1)));
}
