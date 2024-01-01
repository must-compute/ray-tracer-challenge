#include <gtest/gtest.h>

#include "../src/Transformations.h"
#include "../src/Tuple.h"
#include "../src/Matrix.h"
#include <numbers>
#include <cmath>

TEST(Transformations, MultiplyTranslation) {
  const auto transform = tf::translation(5.0, -3.0, 2.0);
  const auto point = Point(-3.0, 4.0, 5.0);
  EXPECT_EQ(transform * point, Point(2.0, 1.0, 7.0));
}

TEST(Transformations, MultiplyTranslationInverse) {
  const auto transform = tf::translation(5.0, -3.0, 2.0);
  const auto inverse_transform = transform.inverse();
  const auto point = Point(-3.0, 4.0, 5.0);
  EXPECT_EQ(inverse_transform * point, Point(-8.0, 7.0, 3.0));
  EXPECT_EQ(transform * (inverse_transform * point), point);
}

TEST(Transformations, TranslationVectorNoEffect) {
  const auto transform = tf::translation(5.0, -3.0, 2.0);
  const auto vector = Vector(-3.0, 4.0, 5.0);
  EXPECT_EQ(transform * vector, vector);
}

TEST(Transformations, ScalingPoint) {
  const auto transform = tf::scaling(2.0, 3.0, 4.0);
  const auto point = Point(-4.0, 6.0, 8.0);
  EXPECT_EQ(transform * point, Point(-8.0, 18.0, 32.0));
}

TEST(Transformations, ScalingVector) {
  const auto transform = tf::scaling(2.0, 3.0, 4.0);
  const auto vector = Vector(-4.0, 6.0, 8.0);
  EXPECT_EQ(transform * vector, Vector(-8.0, 18.0, 32.0));
}

TEST(Transformations, ScalingInverse) {
  const auto transform = tf::scaling(2.0, 3.0, 4.0);
  const auto inverse_transform = transform.inverse();
  const auto vector = Vector(-4.0, 6.0, 8.0);
  EXPECT_EQ(inverse_transform * vector, Vector(-2.0, 2.0, 2.0));
  EXPECT_EQ(inverse_transform * (transform * vector), vector);
}

TEST(Transformations, ScalingReflection) {
  const auto transform = tf::scaling(-1.0, 1.0, 1.0);
  const auto point = Point(2.0, 3.0, 4.0);
  EXPECT_EQ(transform * point, Point(-2.0, 3.0, 4.0));
}

TEST(Transformations, RotationX) {
  using namespace std::numbers;
  const auto point = Point(0.0, 1.0, 0.0);
  const auto half_quarter = tf::rotation_x(pi / 4.0);
  const auto full_quarter = tf::rotation_x(pi / 2.0);
  EXPECT_EQ(half_quarter * point, Point(0.0, std::sqrt(2.0) / 2.0, std::sqrt(2.0) / 2.0));
  EXPECT_EQ(full_quarter * point, Point(0.0, 0.0, 1.0));
}

TEST(Transformations, RotationXInverse) {
  using namespace std::numbers;
  const auto point = Point(0.0, 1.0, 0.0);
  const auto half_quarter = tf::rotation_x(pi / 4.0);
  const auto inverse = half_quarter.inverse();
  EXPECT_EQ(inverse * point, Point(0.0, std::sqrt(2.0) / 2.0, -std::sqrt(2.0) / 2.0));
}

TEST(Transformations, RotationY) {
  using namespace std::numbers;
  const auto point = Point(0.0, 0.0, 1.0);
  const auto half_quarter = tf::rotation_y(pi / 4.0);
  const auto full_quarter = tf::rotation_y(pi / 2.0);
  EXPECT_EQ(half_quarter * point, Point(std::sqrt(2.0) / 2.0, 0.0, std::sqrt(2.0) / 2.0));
  EXPECT_EQ(full_quarter * point, Point(1.0, 0.0, 0.0));
}

TEST(Transformations, RotationZ) {
  using namespace std::numbers;
  const auto point = Point(0.0, 1.0, 0.0);
  const auto half_quarter = tf::rotation_z(pi / 4.0);
  const auto full_quarter = tf::rotation_z(pi / 2.0);
  EXPECT_EQ(half_quarter * point, Point(-std::sqrt(2.0) / 2.0, std::sqrt(2.0) / 2.0, 0.0));
  EXPECT_EQ(full_quarter * point, Point(-1.0, 0.0, 0.0));
}

TEST(Transformations, ShearingXY) {
  const auto transform = tf::shearing(1.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  const auto point = Point(2.0, 3.0, 4.0);
  EXPECT_EQ(transform * point, Point(5.0, 3.0, 4.0));
}

TEST(Transformations, ShearingXZ) {
  const auto transform = tf::shearing(0.0, 1.0, 0.0, 0.0, 0.0, 0.0);
  const auto point = Point(2.0, 3.0, 4.0);
  EXPECT_EQ(transform * point, Point(6.0, 3.0, 4.0));
}

TEST(Transformations, ShearingYX) {
  const auto transform = tf::shearing(0.0, 0.0, 1.0, 0.0, 0.0, 0.0);
  const auto point = Point(2.0, 3.0, 4.0);
  EXPECT_EQ(transform * point, Point(2.0, 5.0, 4.0));
}

TEST(Transformations, ShearingYZ) {
  const auto transform = tf::shearing(0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
  const auto point = Point(2.0, 3.0, 4.0);
  EXPECT_EQ(transform * point, Point(2.0, 7.0, 4.0));
}

TEST(Transformations, ShearingZX) {
  const auto transform = tf::shearing(0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  const auto point = Point(2.0, 3.0, 4.0);
  EXPECT_EQ(transform * point, Point(2.0, 3.0, 6.0));
}

TEST(Transformations, ShearingZY) {
  const auto transform = tf::shearing(0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
  const auto point = Point(2.0, 3.0, 4.0);
  EXPECT_EQ(transform * point, Point(2.0, 3.0, 7.0));
}

TEST(Transformations, AllInSequence) {
  using namespace std::numbers;
  const auto point = Point(1.0, 0.0, 1.0);
  const auto A = tf::rotation_x(pi / 2.0);
  const auto B = tf::scaling(5.0, 5.0, 5.0);
  const auto C = tf::translation(10.0, 5.0, 7.0);

  const auto p2 = A * point;
  EXPECT_EQ(p2, Point(1.0, -1.0, 0.0));

  const auto p3 = B * p2;
  EXPECT_EQ(p3, Point(5.0, -5.0, 0.0));

  const auto p4 = C * p3;
  EXPECT_EQ(p4, Point(15.0, 0.0, 7.0));
}

TEST(Transformations, AllChained) {
  using namespace std::numbers;
  const auto point = Point(1.0, 0.0, 1.0);
  const auto A = tf::rotation_x(pi / 2.0);
  const auto B = tf::scaling(5.0, 5.0, 5.0);
  const auto C = tf::translation(10.0, 5.0, 7.0);
  const auto transform = C * B * A;
  EXPECT_EQ(transform * point, Point(15.0, 0.0, 7.0));
}

TEST(Transformations, TransformationMatrixForTheDefaultOrientation) {
  const auto from = Point(0.0, 0.0, 0.0);
  const auto to = Point(0.0, 0.0, -1.0);
  const auto up = Vector(0.0, 1.0, 0.0);
  const auto t = tf::view_transform(from, to, up);
  EXPECT_EQ(t, tf::Transform::identity());
}

TEST(Transformations, ViewTransformationMatrixInDirectionPosZ) {
  // this is like looking into a mirror
  const auto from = Point(0.0, 0.0, 0.0);
  const auto to = Point(0.0, 0.0, 1.0);
  const auto up = Vector(0.0, 1.0, 0.0);
  const auto t = tf::view_transform(from, to, up);
  EXPECT_EQ(t, tf::scaling(-1.0, 1.0, -1.0));
}

TEST(Transformations, ViewTransformationMovesTheWorld) {
  const auto from = Point(0.0, 0.0, 8.0);
  const auto to = Point(0.0, 0.0, 0.0);
  const auto up = Vector(0.0, 1.0, 0.0);
  const auto t = tf::view_transform(from, to, up);
  EXPECT_EQ(t, tf::translation(0.0, 0.0, -8.0));
}

TEST(Transformations, ArbitraryViewTransformation) {
  const auto from = Point(1.0, 3.0, 2.0);
  const auto to = Point(4.0, -2.0, 8.0);
  const auto up = Vector(1.0, 1.0, 0.0);
  const auto t = tf::view_transform(from, to, up);
  const auto expected_transform = tf::Transform{
      std::array<std::array<double, 4>, 4>{
          {
              {-0.50709, 0.50709, 0.67612, -2.36643},
              {0.76772, 0.60609, 0.12122, -2.82843},
              {-0.35857, 0.59761, -0.71714, 0.0},
              {0.0, 0.0, 0.0, 1.0}
          }
      }
  };
  EXPECT_EQ(t, expected_transform);
}

