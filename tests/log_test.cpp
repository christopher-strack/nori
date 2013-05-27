#include <gtest/gtest.h>
#include <nori/log.h>


TEST(log_info, log_all_priorities) {
    nori::log_info("info");
    nori::log_warning("warning");
    nori::log_error("error");
}

TEST(log_info, log_with_arguments) {
    nori::log_info("info %s", "argument");
}
