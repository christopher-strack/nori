#include <gtest/gtest.h>
#include <nori/texture.h>
#include <nori/image.h>


TEST(texture, construct) {
    nori::image image("assets/image.png");
    nori::texture t(image);

    ASSERT_EQ(t.size(), image.size());
}

TEST(texture, bind) {
    nori::image image("assets/image.png");
    nori::texture t(image);
    t.bind();
}
