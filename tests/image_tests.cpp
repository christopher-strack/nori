#include <gtest/gtest.h>
#include <nori/image.h>

#include <vector>
#include <boost/assign.hpp>


TEST(image, construct) {
    nori::image image("assets/image.png");

    ASSERT_EQ(image.size(), nori::size(2, 2));
}

TEST(image, invalid_path) {
    nori::image image("assets/invalid_image.png");

    ASSERT_EQ(image.size(), nori::size(0, 0));
    ASSERT_EQ(image.data().size(), 0);
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
