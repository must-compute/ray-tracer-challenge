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
