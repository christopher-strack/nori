#include "precompiled.h"
#include <gmock/gmock.h>
#include <nori/sprite.h>


TEST(sprite, construct) {
    nori::sprite sprite("assets/sprite.png");
    ASSERT_EQ(sprite.image_file(), "assets/sprite.png");
}
