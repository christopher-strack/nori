#include "precompiled.h"
#include "image_mock.h"

#include <gmock/gmock.h>
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
    ASSERT_TRUE(atlas.add(image));
}

TEST(texture_atlas, dont_create_overlapping_coords) {
    nori::texture_atlas atlas(nori::size(10, 10));
    nori::testing::image_mock image(nori::size(5, 5));

    auto coords = atlas.add(image);
    ASSERT_TRUE(coords);
    ASSERT_EQ(* coords, nori::rectangle_f(0.0f, 0.0f, 0.5f, 0.5f));

    coords = atlas.add(image);
    ASSERT_TRUE(coords);
    ASSERT_EQ(*coords, nori::rectangle_f(0.5f, 0.0f, 1.0f, 0.5f));

    coords = atlas.add(image);
    ASSERT_TRUE(coords);
    ASSERT_EQ(*coords, nori::rectangle_f(0.0f, 0.5f, 0.5f, 1.0f));

    coords = atlas.add(image);
    ASSERT_TRUE(coords);
    ASSERT_EQ(*coords, nori::rectangle_f(0.5f, 0.5f, 1.0f, 1.0f));

    coords = atlas.add(image);
    ASSERT_FALSE(coords);
}
