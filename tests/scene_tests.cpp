#include "precompiled.h"
#include "renderer_mock.h"

#include <gmock/gmock.h>

#include <nori/scene.h>
#include <nori/slicer.h>

using ::testing::_;


TEST(scene, construct) {
    nori::scene();
}

TEST(scene, add_sprite) {
    nori::scene scene;

    auto sprite = scene.add_sprite("assets/sprite.png");
    ASSERT_EQ(sprite->position(), nori::point_f(0, 0));
    ASSERT_EQ(sprite->size(), nori::size_f(2, 2));
}

TEST(scene, add_with_equal_parameters_returns_equal_sprites) {
    nori::scene scene;

    auto sprite1 = scene.add_sprite("assets/sprite.png");
    auto sprite2 = scene.add_sprite("assets/sprite.png");
    ASSERT_EQ(sprite1->position(), sprite2->position());
    ASSERT_EQ(sprite1->size(), sprite2->size());
}

TEST(scene, render) {
    nori::testing::renderer_mock renderer;
    nori::scene scene;
    scene.add_sprite("assets/sprite.png");

    EXPECT_CALL(renderer, render(_, _, _, _)).Times(1);
    scene.render(renderer);
}

TEST(scene, remove_sprite) {
    nori::scene scene;
    auto sprite = scene.add_sprite("assets/sprite.png");

    bool result = scene.remove_sprite(sprite);
    ASSERT_TRUE(result);

    result = scene.remove_sprite(sprite);
    ASSERT_FALSE(result);

    nori::testing::renderer_mock renderer;
    EXPECT_CALL(renderer, render(_, _, _, _)).Times(0);
    scene.render(renderer);
}

TEST(scene, add_sliced_sprite) {
    nori::scene scene;
    nori::grid_slicer slicer(1, 1);

    auto sprite = scene.add_sprite("assets/sprite.png", slicer);
    ASSERT_EQ(sprite->position(), nori::point_f(0, 0));
    ASSERT_EQ(sprite->size(), nori::size_f(1, 1));
    ASSERT_EQ(sprite->slice_count(), 4);
}
