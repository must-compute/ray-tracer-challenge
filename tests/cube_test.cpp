#include <gtest/gtest.h>

#include <optional>

#include "Cube.h"
#include "Ray.h"
#include "Tuple.h"

TEST(Cube, RayIntersectsCube) {
  const std::vector<std::tuple<std::string, Point, Vector, double, double>> expected_results = {
      {"+x", Point{5.0, 0.5, 0.0}, Vector{-1.0, 0.0, 0.0}, 4.0, 6.0},
      {"-x", Point{-5.0, 0.5, 0.0}, Vector{1.0, 0.0, 0.0}, 4.0, 6.0},
      {"+y", Point{0.5, 5.0, 0.0}, Vector{0.0, -1.0, 0.0}, 4.0, 6.0},
      {"-y", Point{0.5, -5.0, 0.0}, Vector{0.0, 1.0, 0.0}, 4.0, 6.0},
      {"+z", Point{0.5, 0.0, 5.0}, Vector{0.0, 0.0, -1.0}, 4.0, 6.0},
      {"-z", Point{0.5, 0.0, -5.0}, Vector{0.0, 0.0, 1.0}, 4.0, 6.0},
      {"inside", Point{0.0, 0.5, 0.0}, Vector{0.0, 0.0, 1.0}, -1.0, 1.0},
  };

  for (const auto &expected_result : expected_results) {
    const auto [case_name, origin, direction, expected_t1, expected_t2] = expected_result;
    auto cube = Cube{};
    const auto ray = Ray{origin, direction};
    const auto xs = cube.local_intersect(ray);
    ASSERT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, expected_t1);
    EXPECT_EQ(xs[1].t, expected_t2);
  }
}

TEST(Cube, RayMissesCube) {
  const std::vector<std::tuple<Point, Vector>> expected_results = {
      {Point{-2.0, 0.0, 0.0}, Vector{0.2673, 0.5345, 0.8018}},
      {Point{0.0, -2.0, 0.0}, Vector{0.8018, 0.2673, 0.5345}},
      {Point{0.0, 0.0, -2.0}, Vector{0.5345, 0.8018, 0.2673}},
      {Point{2.0, 0.0, 2.0}, Vector{0.0, 0.0, -1.0}},
      {Point{0.0, 2.0, 2.0}, Vector{0.0, -1.0, 0.0}},
      {Point{2.0, 2.0, 0.0}, Vector{-1.0, 0.0, 0.0}},
  };

  for (const auto &expected_result : expected_results) {
    const auto [origin, direction] = expected_result;
    auto cube = Cube{};
    const auto ray = Ray{origin, direction};
    const auto xs = cube.local_intersect(ray);
    EXPECT_EQ(xs.size(), 0);
  }
}

TEST(Cube, NormalOnSurfaceOfCube) {
  const std::vector<std::tuple<Point, Vector>> test_table = {
      {Point{1.0, 0.5, -0.8}, Vector{1.0, 0.0, 0.0}},
      {Point{-1.0, -0.2, 0.9}, Vector{-1.0, 0.0, 0.0}},
      {Point{-0.4, 1.0, -0.1}, Vector{0.0, 1.0, 0.0}},
      {Point{0.3, -1.0, -0.7}, Vector{0.0, -1.0, 0.0}},
      {Point{-0.6, 0.3, 1.0}, Vector{0.0, 0.0, 1.0}},
      {Point{0.4, 0.4, -1.0}, Vector{0.0, 0.0, -1.0}},
      {Point{1.0, 1.0, 1.0}, Vector{1.0, 0.0, 0.0}},
      {Point{-1.0, -1.0, -1.0}, Vector{-1.0, 0.0, 0.0}},
  };

  for (const auto &[input_point, expected_normal] : test_table) {
    auto cube = Cube{};
    EXPECT_EQ(cube.local_normal_at(input_point, std::nullopt), expected_normal);
  }
}
