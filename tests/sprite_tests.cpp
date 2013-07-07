#include "precompiled.h"
#include "renderer_mock.h"
#include <nori/animation.h>
#include <nori/sprite.h>
#include <nori/scene.h>
#include <nori/texture_atlas.h>

#include <gmock/gmock.h>
#include <boost/assign.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/counting_range.hpp>


using ::testing::_;
using ::testing::ByRef;
using ::testing::Eq;


class simple_sprite_test : public ::testing::Test {
public:
    simple_sprite_test() {
        nori::texture_parts parts;
        parts.push_back(
            std::make_tuple(
                std::make_shared<nori::texture_atlas>(nori::size(32, 32)),
                nori::rectangle_f(0, 0, 1.0f, 1.0f)));
        sprite = std::make_shared<nori::sprite>(parts);
    }

    nori::sprite_ptr sprite;
};


TEST_F(simple_sprite_test, construct) {
    ASSERT_EQ(sprite->size(), nori::size(32, 32));
    ASSERT_EQ(sprite->position(), nori::point(0, 0));
}

TEST_F(simple_sprite_test, size) {
    sprite->set_size(nori::size_f(100, 200));
    ASSERT_EQ(sprite->size(), nori::size_f(100, 200));
}

TEST_F(simple_sprite_test, position) {
    sprite->set_position(nori::point_f(100, 200));
    ASSERT_EQ(sprite->position(), nori::point_f(100, 200));
}

TEST_F(simple_sprite_test, render) {
    nori::testing::renderer_mock renderer;

    sprite->set_size(nori::size_f(100, 200));
    sprite->set_position(nori::point_f(300, 400));

    nori::size_f expected_size(100, 200);
    nori::point_f expected_pos(300, 400);
    EXPECT_CALL(renderer, render(
            _, _,
            Eq(ByRef(expected_pos)),
            Eq(ByRef(expected_size))))
        .Times(1);
    sprite->render(renderer);
}

TEST_F(simple_sprite_test, animate_out_of_range_is_ignored) {
    sprite->set_animation(nori::animation(boost::counting_range(1, 3)));
    sprite->update(1.0f);
}


class sliced_sprite_test : public ::testing::Test {
public:
    sliced_sprite_test() {
        using namespace boost::assign;

        nori::texture_atlas_ptr texture =
            std::make_shared<nori::texture_atlas>(nori::size(32, 32));
        nori::texture_parts texture_parts;
        texture_parts +=
            std::make_tuple(texture, nori::rectangle_f(0, 0, 0.5f, 0.5f)),
            std::make_tuple(texture, nori::rectangle_f(0, 0, 0.25f, 0.25f));
        sprite = std::make_shared<nori::sprite>(texture_parts);
    }

    nori::sprite_ptr sprite;
};


TEST_F(sliced_sprite_test, animation) {
    sprite->set_animation(nori::animation(boost::counting_range(0, 2)));
    ASSERT_EQ(sprite->size(), nori::size(16, 16));

    sprite->update(1.0f);
    ASSERT_EQ(sprite->size(), nori::size(8, 8));
}

TEST_F(sliced_sprite_test, set_animation_updates_immediatly) {
    using namespace boost::adaptors;

    sprite->set_animation(nori::animation(boost::counting_range(0, 2) | reversed));
    ASSERT_EQ(sprite->size(), nori::size(8, 8));
}
