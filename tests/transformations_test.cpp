#include <gtest/gtest.h>

#include "../src/Matrix.h"
#include "../src/Transformations.h"
#include "../src/Tuple.h"
#include <numbers>
#include <cmath>


TEST(Transformations, MultiplyTranslation) {
    const auto transform = tf::translation(5.0, -3.0, 2.0);
    const auto point = make_point(-3.0, 4.0, 5.0);
    EXPECT_EQ(transform * point, make_point(2.0, 1.0, 7.0));
}

TEST(Transformations, MultiplyTranslationInverse) {
    const auto transform = tf::translation(5.0, -3.0, 2.0);
    const auto inverse_transform = transform.inverse();
    const auto point = make_point(-3.0, 4.0, 5.0);
    EXPECT_EQ(inverse_transform * point, make_point(-8.0, 7.0, 3.0));
    EXPECT_EQ(transform * (inverse_transform * point), point);
}

TEST(Transformations, TranslationVectorNoEffect) {
    const auto transform = tf::translation(5.0, -3.0, 2.0);
    const auto vector = make_vector(-3.0, 4.0, 5.0);
    EXPECT_EQ(transform * vector, vector);
}

TEST(Transformations, ScalingPoint) {
    const auto transform = tf::scaling(2.0, 3.0, 4.0);
    const auto point = make_point(-4.0, 6.0, 8.0);
    EXPECT_EQ(transform * point, make_point(-8.0, 18.0, 32.0));
}

TEST(Transformations, ScalingVector) {
    const auto transform = tf::scaling(2.0, 3.0, 4.0);
    const auto vector = make_vector(-4.0, 6.0, 8.0);
    EXPECT_EQ(transform * vector, make_vector(-8.0, 18.0, 32.0));
}

TEST(Transformations, ScalingInverse) {
    const auto transform = tf::scaling(2.0, 3.0, 4.0);
    const auto inverse_transform = transform.inverse();
    const auto vector = make_vector(-4.0, 6.0, 8.0);
    EXPECT_EQ(inverse_transform * vector, make_vector(-2.0, 2.0, 2.0));
    EXPECT_EQ(inverse_transform * (transform * vector), vector);
}

TEST(Transformations, ScalingReflection) {
    const auto transform = tf::scaling(-1.0, 1.0, 1.0);
    const auto point = make_point(2.0, 3.0, 4.0);
    EXPECT_EQ(transform * point, make_point(-2.0, 3.0, 4.0));
}

TEST(Transformations, RotationX) {
    using namespace std::numbers;
    const auto point = make_point(0.0, 1.0, 0.0);
    const auto half_quarter = tf::rotation_x(pi / 4.0);
    const auto full_quarter = tf::rotation_x(pi / 2.0);
    EXPECT_EQ(half_quarter * point, make_point(0.0, std::sqrt(2.0) / 2.0, std::sqrt(2.0) / 2.0));
    EXPECT_EQ(full_quarter * point, make_point(0.0, 0.0, 1.0));
}

TEST(Transformations, RotationXInverse) {
    using namespace std::numbers;
    const auto point = make_point(0.0, 1.0, 0.0);
    const auto half_quarter = tf::rotation_x(pi / 4.0);
    const auto inverse = half_quarter.inverse();
    EXPECT_EQ(inverse * point, make_point(0.0, std::sqrt(2.0) / 2.0, -std::sqrt(2.0) / 2.0));
}

TEST(Transformations, RotationY) {
    using namespace std::numbers;
    const auto point = make_point(0.0, 0.0, 1.0);
    const auto half_quarter = tf::rotation_y(pi / 4.0);
    const auto full_quarter = tf::rotation_y(pi / 2.0);
    EXPECT_EQ(half_quarter * point, make_point(std::sqrt(2.0) / 2.0, 0.0, std::sqrt(2.0) / 2.0));
    EXPECT_EQ(full_quarter * point, make_point(1.0, 0.0, 0.0));
}

TEST(Transformations, RotationZ) {
    using namespace std::numbers;
    const auto point = make_point(0.0, 1.0, 0.0);
    const auto half_quarter = tf::rotation_z(pi / 4.0);
    const auto full_quarter = tf::rotation_z(pi / 2.0);
    EXPECT_EQ(half_quarter * point, make_point(-std::sqrt(2.0) / 2.0, std::sqrt(2.0) / 2.0, 0.0));
    EXPECT_EQ(full_quarter * point, make_point(-1.0, 0.0, 0.0));
}

TEST(Transformations, ShearingXY) {
    const auto transform = tf::shearing(1.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    const auto point = make_point(2.0, 3.0, 4.0);
    EXPECT_EQ(transform * point, make_point(5.0, 3.0, 4.0));
}

TEST(Transformations, ShearingXZ) {
    const auto transform = tf::shearing(0.0, 1.0, 0.0, 0.0, 0.0, 0.0);
    const auto point = make_point(2.0, 3.0, 4.0);
    EXPECT_EQ(transform * point, make_point(6.0, 3.0, 4.0));
}

TEST(Transformations, ShearingYX) {
    const auto transform = tf::shearing(0.0, 0.0, 1.0, 0.0, 0.0, 0.0);
    const auto point = make_point(2.0, 3.0, 4.0);
    EXPECT_EQ(transform * point, make_point(2.0, 5.0, 4.0));
}

TEST(Transformations, ShearingYZ) {
    const auto transform = tf::shearing(0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const auto point = make_point(2.0, 3.0, 4.0);
    EXPECT_EQ(transform * point, make_point(2.0, 7.0, 4.0));
}

TEST(Transformations, ShearingZX) {
    const auto transform = tf::shearing(0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    const auto point = make_point(2.0, 3.0, 4.0);
    EXPECT_EQ(transform * point, make_point(2.0, 3.0, 6.0));
}

TEST(Transformations, ShearingZY) {
    const auto transform = tf::shearing(0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    const auto point = make_point(2.0, 3.0, 4.0);
    EXPECT_EQ(transform * point, make_point(2.0, 3.0, 7.0));
}

TEST(Transformations, AllInSequence) {
    using namespace std::numbers;
    const auto point = make_point(1.0, 0.0, 1.0);
    const auto A = tf::rotation_x(pi / 2.0);
    const auto B = tf::scaling(5.0, 5.0, 5.0);
    const auto C = tf::translation(10.0, 5.0, 7.0);

    const auto p2 = A * point;
    EXPECT_EQ(p2, make_point(1.0, -1.0, 0.0));

    const auto p3 = B * p2;
    EXPECT_EQ(p3, make_point(5.0, -5.0, 0.0));

    const auto p4 = C * p3;
    EXPECT_EQ(p4, make_point(15.0, 0.0, 7.0));
}

TEST(Transformations, AllChained) {
    using namespace std::numbers;
    const auto point = make_point(1.0, 0.0, 1.0);
    const auto A = tf::rotation_x(pi / 2.0);
    const auto B = tf::scaling(5.0, 5.0, 5.0);
    const auto C = tf::translation(10.0, 5.0, 7.0);
    const auto transform = C * B * A;
    EXPECT_EQ(transform * point, make_point(15.0, 0.0, 7.0));
}