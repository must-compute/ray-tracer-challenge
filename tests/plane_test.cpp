#include <gtest/gtest.h>

#include <optional>

#include "Ray.h"
#include "Plane.h"
#include "Tuple.h"

TEST(Plane, NormalIsConstantEverywhere) {
  const auto plane = Plane{};
  const auto expected_normal = Vector(0.0, 1.0, 0.0);
  EXPECT_EQ(plane.local_normal_at(Point(0.0, 0.0, 0.0), std::nullopt), expected_normal);
  EXPECT_EQ(plane.local_normal_at(Point(10.0, 0.0, -10.0), std::nullopt), expected_normal);
  EXPECT_EQ(plane.local_normal_at(Point(-5.0, 0.0, 150.0), std::nullopt), expected_normal);
}

TEST(Plane, IntersectRayParallelToPlane) {
  auto plane = Plane{};
  const auto r = Ray{Point(0.0, 10.0, 0.0), Vector(0.0, 0.0, 1.0)};
  EXPECT_TRUE(plane.local_intersect(r).empty());
}

TEST(Plane, IntersectWithCoplanarRay) {
  auto plane = Plane{};
  const auto r = Ray{Point(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0)};
  EXPECT_TRUE(plane.local_intersect(r).empty());
}

TEST(Plane, IntersectingPlaneFromAbove) {
  auto plane = Plane{};
  const auto r = Ray{Point(0.0, 1.0, 0.0), Vector(0.0, -1.0, 0.0)};
  const auto xs = plane.local_intersect(r);
  ASSERT_EQ(xs.size(), 1);
  EXPECT_EQ(xs[0].t, 1.0);
  ASSERT_TRUE(xs[0].object);
  EXPECT_EQ(*xs[0].object, plane);
}

TEST(Plane, IntersectingPlaneFromBelow) {
  auto plane = Plane{};
  const auto r = Ray{Point(0.0, -1.0, 0.0), Vector(0.0, 1.0, 0.0)};
  const auto xs = plane.local_intersect(r);
  ASSERT_EQ(xs.size(), 1);
  EXPECT_EQ(xs[0].t, 1.0);
  ASSERT_TRUE(xs[0].object);
  EXPECT_EQ(*xs[0].object, plane);
}
