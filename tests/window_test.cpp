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
    ASSERT_EQ(window.size(), nori::window::default_size);

    nori::size new_size(1024, 768);
    window.set_size(new_size);
    ASSERT_EQ(window.size(), new_size);
}
