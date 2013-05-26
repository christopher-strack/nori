#include <gtest/gtest.h>
#include <nori/log.h>


TEST(log, log_all_priorities) {
    nori::log("info");
    nori::log_warning("warning");
    nori::log_error("error");
}

TEST(log, log_with_arguments) {
    nori::log("info %s", "argument");
}
