#include <gtest/gtest.h>
#include <nori/window.h>


TEST(window, construct) {
    nori::window();
}

TEST(window, visible) {
    nori::window win;
    win.set_visible(true);
    ASSERT_EQ(win.visible(), true);
}
