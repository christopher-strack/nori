#include "precompiled.h"
#include "renderer_mock.h"

#include <gmock/gmock.h>

#include <nori/scene.h>
#include <nori/sprite.h>
#include <nori/texture.h>

using ::testing::_;
using ::testing::ByRef;
using ::testing::Eq;


TEST(scene, construct) {
    nori::scene();
}

TEST(scene, add_sprite) {
    nori::scene scene;
    auto sprite_node = scene.add_sprite(nori::make_sprite("assets/sprite.png"));
}

TEST(scene, remove_sprite) {
    nori::scene scene;
    auto sprite_node = scene.add_sprite(nori::make_sprite("assets/sprite.png"));

    bool result = scene.remove_sprite(sprite_node);
    ASSERT_TRUE(result);

    result = scene.remove_sprite(sprite_node);
    ASSERT_FALSE(result);
}

TEST(scene, render) {
    nori::testing::renderer_mock renderer;
    nori::scene scene;
    scene.add_sprite(nori::make_sprite("assets/sprite.png"));

    EXPECT_CALL(renderer, render(_, _, _, _)).Times(1);
    scene.render(renderer);
}

TEST(scene, set_node_size) {
    nori::testing::renderer_mock renderer;
    nori::scene scene;
    auto sprite_node = scene.add_sprite(nori::make_sprite("assets/sprite.png"));

    sprite_node->set_size(nori::size_f(100, 200));
    ASSERT_EQ(sprite_node->size(), nori::size_f(100, 200));
    EXPECT_CALL(renderer, render(_, _, _, Eq(ByRef(nori::size_f(100, 200))))).Times(1);
    scene.render(renderer);
}

TEST(scene, default_node_size) {
    nori::scene scene;
    auto sprite_node = scene.add_sprite(nori::make_sprite("assets/sprite.png"));

    ASSERT_EQ(sprite_node->size(), nori::size_f(2, 2));
}

TEST(scene, set_node_position) {
    nori::testing::renderer_mock renderer;
    nori::scene scene;
    auto sprite_node = scene.add_sprite(nori::make_sprite("assets/sprite.png"));
    ASSERT_EQ(sprite_node->position(), nori::point_f());

    sprite_node->set_position(nori::point_f(100, 200));
    ASSERT_EQ(sprite_node->position(), nori::point_f(100, 200));
    EXPECT_CALL(renderer, render(_, _, Eq(ByRef(nori::point_f(100, 200))), _)).Times(1);
    scene.render(renderer);
}

TEST(scene, map_sprite_to_same_texture_part) {
    nori::scene scene;
    auto sprite = nori::make_sprite("assets/sprite.png");

    auto node1 = scene.add_sprite(sprite);
    auto node2 = scene.add_sprite(sprite);
    ASSERT_EQ(node1->texture(), node2->texture());
    ASSERT_EQ(node1->texture_coords(), node2->texture_coords());
}
