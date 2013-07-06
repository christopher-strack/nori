#include "precompiled.h"
#include "renderer_mock.h"
#include <nori/sprite.h>
#include <nori/scene.h>


using ::testing::_;
using ::testing::ByRef;
using ::testing::Eq;


TEST(sprite, size) {
    nori::testing::renderer_mock renderer;
    nori::scene scene;
    auto sprite = scene.add_sprite("assets/sprite.png");

    sprite->set_size(nori::size_f(100, 200));
    ASSERT_EQ(sprite->size(), nori::size_f(100, 200));
    nori::size_f expected_size(100, 200);
    EXPECT_CALL(renderer, render(_, _, _, Eq(ByRef(expected_size)))).Times(1);
    scene.render(renderer);
}

TEST(sprite, position) {
    nori::testing::renderer_mock renderer;
    nori::scene scene;
    auto sprite = scene.add_sprite("assets/sprite.png");
    ASSERT_EQ(sprite->position(), nori::point_f());

    sprite->set_position(nori::point_f(100, 200));
    ASSERT_EQ(sprite->position(), nori::point_f(100, 200));
    nori::point_f expected_pos(100, 200);
    EXPECT_CALL(renderer, render(_, _, Eq(ByRef(expected_pos)), _)).Times(1);
    scene.render(renderer);
}
