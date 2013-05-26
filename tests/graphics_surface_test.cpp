#include <gtest/gtest.h>
#include <nori/graphics_surface.h>
#include <nori/window.h>


TEST(graphics_surface, construct) {
    nori::window window;
    nori::graphics_surface surface(window);
}

TEST(graphics_surface, size) {
    nori::window window;
    window.set_size(nori::size(500, 300));
    nori::graphics_surface surface(window);

    ASSERT_EQ(surface.size(), window.size());
}

TEST(graphics_surface, clear) {
    nori::window window;
    nori::graphics_surface surface(window);

    surface.clear();
}

TEST(graphics_surface, swap) {
    nori::window window;
    nori::graphics_surface surface(window);

    surface.swap();
}
