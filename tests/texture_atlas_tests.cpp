#include "image_mock.h"

#include <gtest/gtest.h>
#include <nori/texture_atlas.h>

#include <stdexcept>


TEST(texture_atlas, construct) {
    nori::texture_atlas atlas;
    int max_size = nori::texture_atlas::max_atlas_size();
    ASSERT_EQ(atlas.size(), nori::size(max_size, max_size));
}

TEST(texture_atlas, add_image) {
    nori::texture_atlas atlas;
    nori::rectangle_f coords;
    nori::image image("assets/image.png");
    ASSERT_TRUE(atlas.add(image, coords));
}

TEST(texture_atlas, dont_create_overlapping_coords) {
    nori::texture_atlas atlas(nori::size(10, 10));
    nori::rectangle_f coords;
    nori::testing::mock_image image(nori::size(5, 5));
    ASSERT_TRUE(atlas.add(image, coords));
    ASSERT_EQ(coords, nori::rectangle_f(0.0f, 0.0f, 0.5f, 0.5f));
    ASSERT_TRUE(atlas.add(image, coords));
    ASSERT_EQ(coords, nori::rectangle_f(0.5f, 0.0f, 1.0f, 0.5f));
    ASSERT_TRUE(atlas.add(image, coords));
    ASSERT_EQ(coords, nori::rectangle_f(0.0f, 0.5f, 0.5f, 1.0f));
    ASSERT_TRUE(atlas.add(image, coords));
    ASSERT_EQ(coords, nori::rectangle_f(0.5f, 0.5f, 1.0f, 1.0f));
    ASSERT_FALSE(atlas.add(image, coords));
}
