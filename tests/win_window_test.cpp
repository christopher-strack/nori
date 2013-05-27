#include <gtest/gtest.h>

#if defined(WIN32)

#include <nori/detail/win_window.h>

class testable_window : public nori::detail::win_window, public testing::Test {
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

#endif
