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

TEST(window, title) {
    nori::window window;
    ASSERT_EQ(window.title(), "");

    window.set_title("test title");
    ASSERT_EQ(window.title(), "test title");
}


class testable_window : public nori::window, public testing::Test {
public:
    void post_close_message() {
        _post_message(WM_CLOSE, 0, 0);
    }

private:
    void _post_message(UINT msg, WPARAM wparam, LPARAM lparam) {
        ::PostMessage(handle(), msg, wparam, lparam);
    }
};

TEST_F(testable_window, dispatch_messages) {
    post_close_message();
    ASSERT_FALSE(closed());

    dispatch_messages();
    ASSERT_TRUE(closed());
}
