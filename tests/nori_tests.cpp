#include "output_printer.h"
#include <gtest/gtest.h>


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    ::testing::UnitTest& unit_test = *::testing::UnitTest::GetInstance();
    ::testing::TestEventListeners& listeners = unit_test.listeners();
    listeners.Append(new nori::testing::output_printer());

    return RUN_ALL_TESTS();
}
