#include <gtest/gtest.h>

#include <optional>

#include "Tuple.h"
#include "Triangle.h"

TEST(Triangle, ConstructingTriangle) {
  const auto p1 = make_point(0.0, 1.0, 0.0);
  const auto p2 = make_point(-1.0, 0.0, 0.0);
  const auto p3 = make_point(1.0, 0.0, 0.0);
  const auto triangle = Triangle{p1, p2, p3};
  EXPECT_EQ(triangle.p1(), p1);
  EXPECT_EQ(triangle.p2(), p2);
  EXPECT_EQ(triangle.p3(), p3);
  EXPECT_EQ(triangle.e1(), make_vector(-1.0, -1.0, 0.0));
  EXPECT_EQ(triangle.e2(), make_vector(1.0, -1.0, 0.0));
  EXPECT_EQ(triangle.normal(), make_vector(0.0, 0.0, -1.0));
}

TEST(Triangle, FindingNormalOnTriangle) {
  const auto p1 = make_point(0.0, 1.0, 0.0);
  const auto p2 = make_point(-1.0, 0.0, 0.0);
  const auto p3 = make_point(1.0, 0.0, 0.0);
  const auto triangle = Triangle{p1, p2, p3};

  EXPECT_EQ(triangle.local_normal_at(make_point(0.0, 0.5, 0.0), std::nullopt), triangle.normal());
  EXPECT_EQ(triangle.local_normal_at(make_point(-0.5, 0.75, 0.0), std::nullopt), triangle.normal());
  EXPECT_EQ(triangle.local_normal_at(make_point(0.5, 0.25, 0.0), std::nullopt), triangle.normal());
}

TEST(Triangle, IntersectingRayParallelToTriangle) {
  const auto p1 = make_point(0.0, 1.0, 0.0);
  const auto p2 = make_point(-1.0, 0.0, 0.0);
  const auto p3 = make_point(1.0, 0.0, 0.0);
  auto triangle = Triangle{p1, p2, p3};

  const auto ray = Ray{make_point(0.0, -1.0, -2.0), make_vector(0.0, 1.0, 0.0)};
  EXPECT_TRUE(triangle.local_intersect(ray).empty());
}

TEST(Triangle, RayMissesP1P3Edge) {
  const auto p1 = make_point(0.0, 1.0, 0.0);
  const auto p2 = make_point(-1.0, 0.0, 0.0);
  const auto p3 = make_point(1.0, 0.0, 0.0);
  auto triangle = Triangle{p1, p2, p3};

  const auto ray = Ray{make_point(1.0, 1.0, -2.0), make_vector(0.0, 0.0, 1.0)};
  EXPECT_TRUE(triangle.local_intersect(ray).empty());
}

TEST(Triangle, RayMissesP1P2Edge) {
  const auto p1 = make_point(0.0, 1.0, 0.0);
  const auto p2 = make_point(-1.0, 0.0, 0.0);
  const auto p3 = make_point(1.0, 0.0, 0.0);
  auto triangle = Triangle{p1, p2, p3};

  const auto ray = Ray{make_point(-1.0, 1.0, -2.0), make_vector(0.0, 0.0, 1.0)};
  EXPECT_TRUE(triangle.local_intersect(ray).empty());
}

TEST(Triangle, RayMissesP2P3Edge) {
  const auto p1 = make_point(0.0, 1.0, 0.0);
  const auto p2 = make_point(-1.0, 0.0, 0.0);
  const auto p3 = make_point(1.0, 0.0, 0.0);
  auto triangle = Triangle{p1, p2, p3};

  const auto ray = Ray{make_point(0.0, -1.0, -2.0), make_vector(0.0, 0.0, 1.0)};
  EXPECT_TRUE(triangle.local_intersect(ray).empty());
}

TEST(Triangle, RayHitsTriangle) {
  const auto p1 = make_point(0.0, 1.0, 0.0);
  const auto p2 = make_point(-1.0, 0.0, 0.0);
  const auto p3 = make_point(1.0, 0.0, 0.0);
  auto triangle = Triangle{p1, p2, p3};

  const auto ray = Ray{make_point(0.0, 0.5, -2.0), make_vector(0.0, 0.0, 1.0)};
  const auto xs = triangle.local_intersect(ray);
  ASSERT_EQ(xs.size(), 1);
  EXPECT_EQ(xs.front().t, 2.0);
}

TEST(Triangle, TriangleHasBoundingBox) {
  const auto p1 = make_point(-3.0, 7.0, 2.0);
  const auto p2 = make_point(6.0, 2.0, -4.0);
  const auto p3 = make_point(2.0, -1.0, -1.0);
  auto triangle = Triangle{p1, p2, p3};
  const auto bbox = triangle.make_bounding_box();
  EXPECT_EQ(bbox.minimum(), make_point(-3.0, -1.0, -4.0));
  EXPECT_EQ(bbox.maximum(), make_point(6.0, 7.0, 2.0));
}