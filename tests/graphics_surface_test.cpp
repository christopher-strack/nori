#include <gtest/gtest.h>
#include <nori/graphics_surface.h>
#include <nori/window.h>


TEST(graphics_surface, construct) {
    HWND hwnd = 0;
    nori::window window;
    nori::graphics_surface surface(hwnd, window);
}

TEST(graphics_surface, size) {
    HWND hwnd = 0;
    nori::window window;
    window.set_size(nori::size(500, 300));
    nori::graphics_surface surface(hwnd, window);

    ASSERT_EQ(surface.size(), window.size());
}

TEST(graphics_surface, clear) {
    HWND hwnd = 0;
    nori::window window;
    nori::graphics_surface surface(hwnd, window);

    surface.clear();
}

TEST(graphics_surface, swap) {
    HWND hwnd = 0;
    nori::window window;
    nori::graphics_surface surface(hwnd, window);

    surface.swap();
}
