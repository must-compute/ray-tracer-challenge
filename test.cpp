#include <gtest/gtest.h>

#include <fstream>
#include <filesystem>
#include <map>
#include "Tuple.h"


class RayTracerFixutre : public ::testing::Test {
protected:

    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(RayTracerFixutre, PlaceholderTest) {
    EXPECT_EQ(1 + 1, 2);
}

// TODO do we have EXPECT WITHIN EPSILON

TEST_F(RayTracerFixutre, TupleAndWBasicTest) {
    double x, y, z, w;
    x = 1.0;
    y = 2.2;
    z = 3.5;
    w = 1.0;
    const Tuple t = Tuple(x, y, z, w);
    EXPECT_FLOAT_EQ(t.x, x);
    EXPECT_FLOAT_EQ(t.y, y);
    EXPECT_FLOAT_EQ(t.z, z);
    EXPECT_FLOAT_EQ(t.w, w);
    EXPECT_TRUE(t.is_point());
    EXPECT_FALSE(t.is_vector());
}
