#include <gtest/gtest.h>

#include <map>
#include "Tuple.h"


class RayTracerFixture : public ::testing::Test {
protected:

    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(RayTracerFixture, PlaceholderTest) {
    EXPECT_EQ(1 + 1, 2);
}

// TODO do we have EXPECT WITHIN EPSILON

TEST_F(RayTracerFixture, TupleBasic) {
    double x, y, z, w;
    x = 1.0;
    y = 2.2;
    z = 3.5;
    w = 1.0;
    const Tuple t = Tuple(x, y, z, w);
    EXPECT_EQ(t.x(), x);
    EXPECT_EQ(t.y(), y);
    EXPECT_EQ(t.z(), z);
    EXPECT_EQ(t.w(), w);
    EXPECT_TRUE(t.is_point());
    EXPECT_FALSE(t.is_vector());
}

TEST_F(RayTracerFixture, TupleFactoryTest) {
    double x = 1.0;
    double y = 2.2;
    double z = 3.5;
    const Tuple point_tuple = make_point(x, y, z);
    const Tuple t1 = Tuple(x, y, z, 1.0);
    EXPECT_EQ(point_tuple, t1);

    const Tuple vector_tuple = make_vector(x, y, z);
    const Tuple t2 = Tuple(x, y, z, 0.0);
    EXPECT_EQ(vector_tuple, t2);
}

TEST_F(RayTracerFixture, TupleAddition) {
    const Tuple t1 = Tuple(3.0, -2.0, 5.0, 1.0);
    const Tuple t2 = Tuple(-2.0, 3.0, 1.0, 0.0);

    EXPECT_EQ(t1 + t2, Tuple(1.0, 1.0, 6.0, 1.0));
}

TEST_F(RayTracerFixture, TupleSubtraction) {
    {
        const Tuple p1 = make_point(3.0, 2.0, 1.0);
        const Tuple p2 = make_point(5.0, 6.0, 7.0);
        EXPECT_EQ(p1 - p2, make_vector(-2.0, -4.0, -6.0));
    }
    {
        const Tuple p1 = make_point(3.0, 2.0, 1.0);
        const Tuple v1 = make_vector(5.0, 6.0, 7.0);
        EXPECT_EQ(p1 - v1, make_point(-2.0, -4.0, -6.0));
    }
    {
        const Tuple v1 = make_vector(3.0, 2.0, 1.0);
        const Tuple v2 = make_vector(5.0, 6.0, 7.0);
        EXPECT_EQ(v1 - v2, make_vector(-2.0, -4.0, -6.0));
    }
    {
        const Tuple v1 = make_vector(0.0, 0.0, 0.0);
        const Tuple v2 = make_vector(5.0, 6.0, 7.0);
        EXPECT_EQ(v1 - v2, make_vector(-5.0, -6.0, -7.0));
    }
}

TEST_F(RayTracerFixture, TupleNegation) {
    {
        const Tuple t1 = make_vector(1.0, 2.0, 3.0);
        EXPECT_EQ(-t1, make_vector(-1.0, -2.0, -3.0));
    }
    {
        const Tuple t1 = make_point(1.0, 2.0, 3.0);
        EXPECT_NE(-t1, make_point(-1.0, -2.0, -3.0));
    }
}


TEST_F(RayTracerFixture, TupleScalarMultiply) {
    {
        const Tuple t = Tuple(1.0, -2.0, 3.0, -4.0);
        EXPECT_EQ(t * 3.5, Tuple(3.5, -7.0, 10.5, -14.0));
    }
    {
        const Tuple t = Tuple(1.0, -2.0, 3.0, -4.0);
        EXPECT_EQ(t * 0.5, Tuple(0.5, -1.0, 1.5, -2.0));
    }
}

TEST_F(RayTracerFixture, TupleScalarDivide) {
    const Tuple t = Tuple(1.0, -2.0, 3.0, -4.0);
    EXPECT_EQ(t / 2.0, Tuple(0.5, -1.0, 1.5, -2.0));
}


TEST_F(RayTracerFixture, TupleMagnitude) {
    {
        const Tuple v = make_vector(1.0, 0.0, 0.0);
        EXPECT_EQ(v.magnitude(), 1.0);
    }
    {
        const Tuple v = make_vector(0.0, 1.0, 0.0);
        EXPECT_EQ(v.magnitude(), 1.0);
    }
    {
        const Tuple v = make_vector(0.0, 0.0, 1.0);
        EXPECT_EQ(v.magnitude(), 1.0);
    }
    {
        const Tuple v = make_vector(1.0, 2.0, 3.0);
        EXPECT_TRUE(within_epsilon(v.magnitude(), std::sqrt(14.0)));
    }
    {
        const Tuple v = make_vector(-1.0, -2.0, -3.0);
        EXPECT_TRUE(within_epsilon(v.magnitude(), std::sqrt(14.0)));
    }
}

TEST_F(RayTracerFixture, TupleNormalize) {
    {
        const Tuple v = make_vector(4.0, 0.0, 0.0);
        EXPECT_EQ(v.normalize(), make_vector(1.0, 0.0, 0.0));
    }
    {
        const Tuple v = make_vector(1.0, 2.0, 3.0);
        const double sqrt_of_fourteen = std::sqrt(14.0);
        EXPECT_EQ(v.normalize(), make_vector(1.0 / sqrt_of_fourteen, 2.0 / sqrt_of_fourteen, 3.0 / sqrt_of_fourteen));
    }
    {
        const Tuple v = make_vector(1.0, 2.0, 3.0);
        EXPECT_TRUE(within_epsilon(v.normalize().magnitude(), 1.0));
    }
}

TEST_F(RayTracerFixture, TupleDotProduct) {
    const Tuple v1 = make_vector(1.0, 2.0, 3.0);
    const Tuple v2 = make_vector(2.0, 3.0, 4.0);
    EXPECT_EQ(v1.dot(v2), 20.0);
}

TEST_F(RayTracerFixture, TupleCrossProduct) {
    const Tuple v1 = make_vector(1.0, 2.0, 3.0);
    const Tuple v2 = make_vector(2.0, 3.0, 4.0);
    const Tuple expected = make_vector(-1.0, 2.0, -1.0);
    EXPECT_EQ(v1.cross(v2), expected);
    EXPECT_EQ(v2.cross(v1), -expected);
}
