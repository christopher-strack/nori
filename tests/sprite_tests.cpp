#include "precompiled.h"
#include <gmock/gmock.h>
#include <nori/sprite.h>


TEST(sprite, construct) {
    nori::sprite sprite("assets/sprite.png");
    ASSERT_EQ(sprite.image_file(), "assets/sprite.png");
}

TEST(sprite, slice_by_size) {
    nori::sprite sprite("assets/sprite.png", nori::size(1, 1));

    ASSERT_EQ(sprite.slice_size(), nori::size(1, 1));
    ASSERT_EQ(sprite.image_file(), "assets/sprite.png");
}
