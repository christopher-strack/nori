#include <gtest/gtest.h>
#include <nori/texture.h>
#include <nori/image.h>

#include <stdexcept>


TEST(texture, construct_from_image) {
    nori::image image("assets/image.png");
    nori::texture t(image);

    ASSERT_EQ(t.size(), image.size());
}

TEST(texture, construct_by_size) {
    nori::size s(256, 256);
    nori::texture t(s);
    t.bind();

    ASSERT_EQ(t.size(), s);
}

TEST(texture, construct_too_big_throws) {
    nori::size s(nori::texture::max_size() + 1, 256);

    ASSERT_THROW(nori::texture t(s), std::runtime_error);
}

TEST(texture, bind_image) {
    nori::image image("assets/image.png");
    nori::texture t(image);
    t.bind();
}
