#include <gtest/gtest.h>
#include <nori/window.h>


TEST(window, construct) {
    nori::window();
}

TEST(window, visible) {
    nori::window win;
    ASSERT_EQ(win.visible(), false);

    win.set_visible(true);
    ASSERT_EQ(win.visible(), true);
}

TEST(window, close) {
    nori::window win;
    ASSERT_EQ(win.closed(), false);

    win.close();
    ASSERT_EQ(win.closed(), true);
}

TEST(window, size) {
    nori::window win;
    ASSERT_EQ(win.size(), nori::window::default_size);

    nori::size new_size(1024, 768);
    win.set_size(new_size);
    ASSERT_EQ(win.size(), new_size);
}
