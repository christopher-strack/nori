#include "precompiled.h"
#include <gtest/gtest.h>
#include <nori/matrix4.h>


TEST(matrix4, construct) {
    nori::matrix4 m;
    for (int i = 0; i < 16; i++) {
        ASSERT_EQ(m.elements[i], 0);
    }
}