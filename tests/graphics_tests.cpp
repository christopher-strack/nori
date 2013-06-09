#include <gtest/gtest.h>
#include <nori/graphics.h>
#include <nori/image.h>

#include <boost/make_shared.hpp>


TEST(graphics, draw) {
    nori::graphics graphics;
    nori::image_ptr image = boost::make_shared<nori::image>("assets/image.png");
    graphics.draw(image, nori::point(10, 20));
}
