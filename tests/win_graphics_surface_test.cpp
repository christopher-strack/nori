#include "precompiled.h"

#if defined(WIN32)

#include <gtest/gtest.h>
#include <nori/graphics_surface.h>
#include <nori/window.h>


class graphics_surface_fixture : public testing::Test {
public:
    graphics_surface_fixture() {
        surface = window.graphics_surface();
    }

    nori::graphics_surface_ptr surface;
    nori::window window;
};


TEST_F(graphics_surface_fixture, size) {
    ASSERT_EQ(surface->size(), window.size());
}

TEST_F(graphics_surface_fixture, clear) {
    surface->clear();
}

TEST_F(graphics_surface_fixture, swap) {
    surface->swap();
}

#endif
