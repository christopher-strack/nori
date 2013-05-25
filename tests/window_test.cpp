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
