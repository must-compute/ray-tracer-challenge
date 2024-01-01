#include <gtest/gtest.h>

#include <limits>
#include <optional>

#include "Cylinder.h"
#include "Ray.h"
#include "Tuple.h"

TEST(Cylinder, RayMissesCylinder) {
  const std::vector<std::tuple<Point, Vector>> test_table = {
      {Point(1.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0)},
      {Point(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0)},
      {Point(0.0, 0.0, -5.0), Vector(1.0, 1.0, 0.0)},
  };

  for (const auto &[origin, direction] : test_table) {
    auto cylinder = Cylinder{};
    const auto ray = Ray{origin, direction.normalize()};
    const auto xs = cylinder.local_intersect(ray);
    ASSERT_EQ(xs.size(), 0);
  }
}

TEST(Cylinder, RayHitsCylinder) {
  const std::vector<std::tuple<Point, Vector, double, double>> test_table = {
      {Point(1.0, 0.0, -5.0), Vector(0.0, 0.0, 1.0), 5.0, 5.0},
      {Point(0.0, 0.0, -5.0), Vector(0.0, 0.0, 1.0), 4.0, 6.0},
      {Point(0.5, 0.0, -5.0), Vector(0.1, 1.0, 1.0), 6.80798, 7.08872},
  };

  for (const auto &[origin, direction, t0, t1] : test_table) {
    auto cylinder = Cylinder{};
    const auto ray = Ray{origin, direction.normalize()};
    const auto xs = cylinder.local_intersect(ray);
    ASSERT_EQ(xs.size(), 2);
    EXPECT_TRUE(within_epsilon(xs[0].t, t0));
    EXPECT_TRUE(within_epsilon(xs[1].t, t1));
  }
}

TEST(Cylinder, NormalVectorOnCylinder) {
  const std::vector<std::tuple<Point, Vector>> test_table = {
      {Point(1.0, 0.0, 0.0), Vector(1.0, 0.0, 0.0)},
      {Point(0.0, 5.0, -1.0), Vector(0.0, 0.0, -1.0)},
      {Point(0.0, -2.0, 1.0), Vector(0.0, 0.0, 1.0)},
      {Point(-1.0, 1.0, 0.0), Vector(-1.0, 0.0, 0.0)},
  };

  for (const auto &[point, normal] : test_table) {
    auto cylinder = Cylinder{};
    EXPECT_EQ(cylinder.local_normal_at(point, std::nullopt), normal);
  }
}

TEST(Cylinder, DefaultMinimumAndMaximumForCylinder) {
  const auto cylinder = Cylinder{};
  EXPECT_EQ(cylinder.minimum(), -std::numeric_limits<double>::infinity());
  EXPECT_EQ(cylinder.maximum(), std::numeric_limits<double>::infinity());
}

TEST(Cylinder, IntersectingConstrainedCylinder) {
  const std::vector<std::tuple<Point, Vector, size_t>> test_table = {
      {Point(0.0, 1.5, 0.0), Vector(0.1, 1.0, 0.0), 0},
      {Point(0.0, 3.0, -5.0), Vector(0.0, 0.0, 1.0), 0},
      {Point(0.0, 0.0, -5.0), Vector(0.0, 0.0, 1.0), 0},
      {Point(0.0, 2.0, -5.0), Vector(0.0, 0.0, 1.0), 0},
      {Point(0.0, 1.0, -5.0), Vector(0.0, 0.0, 1.0), 0},
      {Point(0.0, 1.5, -2.0), Vector(0.0, 0.0, 1.0), 2},
  };

  auto cylinder = Cylinder{};
  cylinder.set_minimum(1.0);
  cylinder.set_maximum(2.0);

  for (const auto &[point, direction, count] : test_table) {
    const auto ray = Ray{point, direction.normalize()};
    EXPECT_EQ(cylinder.local_intersect(ray).size(), count);
  }
}

TEST(Cylinder, DefaultClosedValueForCylinder) {
  const auto cylinder = Cylinder{};
  EXPECT_FALSE(cylinder.closed());
}

TEST(Cylinder, IntersectingCapsOfClosedCylinder) {
  const std::vector<std::tuple<Point, Vector, size_t>> test_table = {
      {Point(0.0, 3.0, 0.0), Vector(0.0, -1.0, 0.0), 2},
      {Point(0.0, 3.0, -2.0), Vector(0.0, -1.0, 2.0), 2},
      {Point(0.0, 4.0, -2.0), Vector(0.0, -1.0, 1.0), 2},
      {Point(0.0, 0.0, -2.0), Vector(0.0, 1.0, 2.0), 2},
      {Point(0.0, -1.0, -2.0), Vector(0.0, 1.0, 1.0), 2},
  };

  auto cylinder = Cylinder{};
  cylinder.set_minimum(1.0);
  cylinder.set_maximum(2.0);
  cylinder.set_closed(true);

  for (const auto &[point, direction, count] : test_table) {
    const auto ray = Ray{point, direction.normalize()};
    EXPECT_EQ(cylinder.local_intersect(ray).size(), count);
  }
}

TEST(Cylinder, NormalVectorOnCylinderEndCaps) {
  const std::vector<std::tuple<Point, Vector>> test_table = {
      {Point(0.0, 1.0, 0.0), Vector(0.0, -1.0, 0.0)},
      {Point(0.5, 1.0, 0.0), Vector(0.0, -1.0, 0.0)},
      {Point(0.0, 1.0, 0.5), Vector(0.0, -1.0, 0.0)},
      {Point(0.0, 2.0, 0.0), Vector(0.0, 1.0, 0.0)},
      {Point(0.5, 2.0, 0.0), Vector(0.0, 1.0, 0.0)},
      {Point(0.0, 2.0, 0.5), Vector(0.0, 1.0, 0.0)},
  };

  auto cylinder = Cylinder{};
  cylinder.set_minimum(1.0);
  cylinder.set_maximum(2.0);
  cylinder.set_closed(true);

  for (const auto &[point, normal] : test_table) {
    EXPECT_EQ(cylinder.local_normal_at(point, std::nullopt), normal);
  }
}
