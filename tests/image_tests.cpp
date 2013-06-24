#include "precompiled.h"
#include <gmock/gmock.h>
#include <nori/image.h>

#include <boost/assign.hpp>

#include <vector>
#include <stdexcept>


TEST(image, construct) {
    nori::image image("assets/image.png");

    ASSERT_EQ(image.size(), nori::size(2, 2));
}

TEST(image, invalid_path) {
    ASSERT_THROW(nori::image("assets/invalid_image.png"), std::runtime_error);
}

TEST(image, data) {
    using namespace boost::assign;

    nori::image image("assets/image.png");

    std::vector<unsigned char> expected_data;
    expected_data +=
        255, 0,   0, 255,
        0, 255,   0, 255,
        0,   0, 255, 255,
        0,   0,   0, 255;

    ASSERT_TRUE(boost::equal(image.data(), expected_data));
}
