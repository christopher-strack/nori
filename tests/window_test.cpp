#include <gtest/gtest.h>
#include <nori/window.h>


TEST(window, construct) {
    nori::window();
}

TEST(window, visible) {
    nori::window window;
    ASSERT_EQ(window.visible(), false);

    window.set_visible(true);
    ASSERT_EQ(window.visible(), true);
}

TEST(window, close) {
    nori::window window;
    ASSERT_EQ(window.closed(), false);

    window.close();
    ASSERT_EQ(window.closed(), true);
}

TEST(window, size) {
    nori::window window;

    nori::size new_size(1024, 768);
    window.set_size(new_size);
    ASSERT_EQ(window.size(), new_size);
}

TEST(window, title) {
    nori::window window;
    ASSERT_EQ(window.title(), "");

    window.set_title("test title");
    ASSERT_EQ(window.title(), "test title");
}

TEST(window, focus) {
    nori::window window;

    window.set_visible(true);
    ASSERT_TRUE(window.focused());
}

TEST(window, graphics_surface) {
    nori::window window;

    nori::graphics_surface_ptr surface = window.graphics_surface();
    ASSERT_TRUE(surface != 0);
}
