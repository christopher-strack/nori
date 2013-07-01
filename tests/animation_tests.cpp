#include "precompiled.h"
#include <gmock/gmock.h>
#include <nori/animation.h>

#include <array>

#include <boost/range/counting_range.hpp>


namespace {

auto default_pattern = boost::counting_range(1, 4);

}


TEST(animation, construct) {
    nori::animation a(default_pattern);
    ASSERT_EQ(a.value(), 1);
}

TEST(animation, advance_to_next_value) {
    nori::animation a(default_pattern);

    a.advance(1.0f);
    ASSERT_EQ(a.value(), 2);
}

TEST(animation, advance_loops) {
    nori::animation a(default_pattern);

    a.advance(1.0f);
    ASSERT_EQ(a.value(), 2);

    a.advance(1.0f);
    ASSERT_EQ(a.value(), 3);

    a.advance(1.0f);
    ASSERT_EQ(a.value(), 1);
}

TEST(animation, advance_skips) {
    nori::animation a(default_pattern);

    a.advance(2.0f);
    ASSERT_EQ(a.value(), 3);
}

TEST(animation, advance_single_element) {
    std::array<int, 1> pattern = {2};
    nori::animation a(pattern);

    a.advance(1.0f);
    ASSERT_EQ(a.value(), 2);

    a.advance(1.0f);
    ASSERT_EQ(a.value(), 2);
}

TEST(animation, set_speed) {
    nori::animation a(default_pattern);

    a.set_speed(0.1f);
    ASSERT_EQ(a.value(), 1);
    ASSERT_EQ(a.speed(), 0.1f);

    a.advance(0.1f);
    ASSERT_EQ(a.value(), 2);

    a.advance(0.1f);
    ASSERT_EQ(a.value(), 3);
}
