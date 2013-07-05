#include "precompiled.h"
#include "renderer_mock.h"

#include <gmock/gmock.h>

#include <nori/scene.h>
#include <nori/slicer.h>
#include <nori/texture.h>

using ::testing::_;
using ::testing::ByRef;
using ::testing::Eq;


TEST(scene, construct) {
    nori::scene();
}

TEST(scene, add_sprite_returns_valid_node) {
    nori::scene scene;

    auto node = scene.add_sprite("assets/sprite.png");
    ASSERT_EQ(node->position(), nori::point_f(0, 0));
    ASSERT_EQ(node->size(), nori::size_f(2, 2));
}

TEST(scene, add_equal_sprites_returns_equal_nodes) {
    nori::scene scene;

    auto node1 = scene.add_sprite("assets/sprite.png");
    auto node2 = scene.add_sprite("assets/sprite.png");
    ASSERT_EQ(node1->position(), node2->position());
    ASSERT_EQ(node1->size(), node2->size());
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
    auto sprite_node = scene.add_sprite("assets/sprite.png");

    bool result = scene.remove_sprite(sprite_node);
    ASSERT_TRUE(result);

    result = scene.remove_sprite(sprite_node);
    ASSERT_FALSE(result);

    nori::testing::renderer_mock renderer;
    EXPECT_CALL(renderer, render(_, _, _, _)).Times(0);
    scene.render(renderer);
}

TEST(scene, set_node_size) {
    nori::testing::renderer_mock renderer;
    nori::scene scene;
    auto sprite_node = scene.add_sprite("assets/sprite.png");

    sprite_node->set_size(nori::size_f(100, 200));
    ASSERT_EQ(sprite_node->size(), nori::size_f(100, 200));
    nori::size_f expected_size(100, 200);
    EXPECT_CALL(renderer, render(_, _, _, Eq(ByRef(expected_size)))).Times(1);
    scene.render(renderer);
}

TEST(scene, set_node_position) {
    nori::testing::renderer_mock renderer;
    nori::scene scene;
    auto sprite_node = scene.add_sprite("assets/sprite.png");
    ASSERT_EQ(sprite_node->position(), nori::point_f());

    sprite_node->set_position(nori::point_f(100, 200));
    ASSERT_EQ(sprite_node->position(), nori::point_f(100, 200));
    nori::point_f expected_pos(100, 200);
    EXPECT_CALL(renderer, render(_, _, Eq(ByRef(expected_pos)), _)).Times(1);
    scene.render(renderer);
}

TEST(scene, add_sliced_sprite_returns_sliced_node) {
    nori::scene scene;

    auto node = scene.add_sprite("assets/sprite.png", nori::grid_slicer(1, 1));
    ASSERT_EQ(node->position(), nori::point_f(0, 0));
    ASSERT_EQ(node->size(), nori::size_f(1, 1));
    ASSERT_EQ(node->slice_count(), 4);
}
