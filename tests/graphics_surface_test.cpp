#include <gtest/gtest.h>
#include <nori/graphics_surface.h>
#include <nori/window.h>


TEST(graphics_surface, construct) {
    nori::window window;
    nori::graphics_surface surface(window);
}
