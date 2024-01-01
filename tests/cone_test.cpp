#include <gtest/gtest.h>

#include <optional>

#include "Cone.h"
#include "Ray.h"
#include "Tuple.h"

TEST(Cone, IntersectingConeWithRay) {
  const std::vector<std::tuple<Point, Vector, double, double>> test_table = {
      {Point{0.0, 0.0, -5.0}, Vector{0.0, 0.0, 1.0}, 5.0, 5.0},
      {Point{0.0, 0.0, -5.0}, Vector{1.0, 1.0, 1.0}, 8.66025, 8.66025},
      {Point{1.0, 1.0, -5.0}, Vector{-0.5, -1.0, 1.0}, 4.55006, 49.44994},
  };

  for (const auto &[origin, direction, t0, t1] : test_table) {
    auto cone = Cone{};
    const auto ray = Ray{origin, direction.normalize()};

    const auto xs = cone.local_intersect(ray);
    ASSERT_EQ(xs.size(), 2);
    EXPECT_TRUE(within_epsilon(xs[0].t, t0));
    EXPECT_TRUE(within_epsilon(xs[1].t, t1));
  }
}

TEST(Cone, InterrsectingConeWithRayParallelToOneOfItsHalves) {
  auto cone = Cone{};
  const auto ray = Ray{Point{0.0, 0.0, -1.0}, Vector{0.0, 1.0, 1.0}.normalize()};

  const auto xs = cone.local_intersect(ray);
  ASSERT_EQ(xs.size(), 1);
  EXPECT_TRUE(within_epsilon(xs[0].t, 0.35355));
}

TEST(Cone, IntersectingConeEndCaps) {
  const std::vector<std::tuple<Point, Vector, size_t>> test_table = {
      {Point{0.0, 0.0, -5.0}, Vector{0.0, 1.0, 0.0}, 0},
      {Point{0.0, 0.0, -0.25}, Vector{0.0, 1.0, 1.0}, 2},
      {Point{0.0, 0.0, -0.25}, Vector{0.0, 1.0, 0.0}, 4},
  };

  auto cone = Cone{};
  cone.set_minimum(-0.5);
  cone.set_maximum(0.5);
  cone.set_closed(true);

  for (const auto &[origin, direction, count] : test_table) {
    const auto ray = Ray{origin, direction.normalize()};
    const auto xs = cone.local_intersect(ray);
    EXPECT_EQ(xs.size(), count);
  }
}

TEST(Cone, ComputeNormalVectorOnCone) {
  const std::vector<std::tuple<Point, Vector>> test_table = {
      {Point{0.0, 0.0, 0.0}, Vector{0.0, 0.0, 0.0}},
      {Point{1.0, 1.0, 1.0}, Vector{1.0, -std::sqrt(2.0), 1.0}},
      {Point{-1.0, -1.0, 0.0}, Vector{-1.0, 1.0, 0.0}},
  };

  auto cone = Cone{};

  for (const auto &[point, expected_normal] : test_table) {

    const auto normal = cone.local_normal_at(point, std::nullopt);
    EXPECT_EQ(normal, expected_normal);
  }
}

