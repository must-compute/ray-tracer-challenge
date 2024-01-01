#include <gtest/gtest.h>

#include "Ray.h"
#include "Sphere.h"
#include "Tuple.h"
#include "Transformations.h"

TEST(Ray, Creation) {
  const auto origin = Point(1.0, 2.0, 3.0);
  const auto direction = Vector(4.0, 5.0, 6.0);
  const auto r = Ray(origin, direction);
  EXPECT_EQ(r.origin(), origin);
  EXPECT_EQ(r.direction(), direction);
}

TEST(Ray, PositionAtT) {
  const auto r = Ray(Point(2.0, 3.0, 4.0), Vector(1.0, 0.0, 0.0));
  EXPECT_EQ(r.position_at_t(0.0), Point(2.0, 3.0, 4.0));
  EXPECT_EQ(r.position_at_t(1.0), Point(3.0, 3.0, 4.0));
  EXPECT_EQ(r.position_at_t(-1.0), Point(1.0, 3.0, 4.0));
  EXPECT_EQ(r.position_at_t(2.5), Point(4.5, 3.0, 4.0));
}

TEST(Ray, IntersectSphereTwoPoints) {
  const auto r = Ray(Point(0.0, 0.0, -5.0), Vector(0.0, 0.0, 1.0));
  auto s = Sphere{};
  const auto intersections = s.intersect(r);

  ASSERT_EQ(intersections.size(), 2);
  EXPECT_EQ(intersections[0].t, 4.0);
  EXPECT_EQ(intersections[1].t, 6.0);
  ASSERT_TRUE(intersections[0].object);
  EXPECT_EQ(*intersections[0].object, s);
  ASSERT_TRUE(intersections[1].object);
  EXPECT_EQ(*intersections[1].object, s);
}

TEST(Ray, IntersectSphereTangent) {
  const auto r = Ray(Point(0.0, 1.0, -5.0), Vector(0.0, 0.0, 1.0));
  auto s = Sphere{};
  const auto intersections = s.intersect(r);

  // Intentionally assert that a tangent intersection returns two identical values, as the book recommends to ease things for later chapters.
  ASSERT_EQ(intersections.size(), 2);
  EXPECT_EQ(intersections[0].t, 5.0);
  EXPECT_EQ(intersections[1].t, 5.0);
  ASSERT_TRUE(intersections[0].object);
  EXPECT_EQ(*intersections[0].object, s);
  ASSERT_TRUE(intersections[1].object);
  EXPECT_EQ(*intersections[1].object, s);
}

TEST(Ray, IntersectSphereMiss) {
  const auto r = Ray(Point(0.0, 2.0, -5.0), Vector(0.0, 0.0, 1.0));
  auto s = Sphere{};
  const auto intersections = s.intersect(r);
  ASSERT_EQ(intersections.size(), 0);
}

TEST(Ray, IntersectOriginatesInsideSphere) {
  const auto r = Ray(Point(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));
  auto s = Sphere{};
  const auto intersections = s.intersect(r);
  ASSERT_EQ(intersections.size(), 2);
  EXPECT_EQ(intersections[0].t, -1.0);
  EXPECT_EQ(intersections[1].t, 1.0);
  ASSERT_TRUE(intersections[0].object);
  EXPECT_EQ(*intersections[0].object, s);
  ASSERT_TRUE(intersections[1].object);
  EXPECT_EQ(*intersections[1].object, s);
}

TEST(Ray, IntersectSphereBehindRay) {
  const auto r = Ray(Point(0.0, 0.0, 5.0), Vector(0.0, 0.0, 1.0));
  auto s = Sphere{};
  const auto intersections = s.intersect(r);
  ASSERT_EQ(intersections.size(), 2);
  EXPECT_EQ(intersections[0].t, -6.0);
  EXPECT_EQ(intersections[1].t, -4.0);
  ASSERT_TRUE(intersections[0].object);
  EXPECT_EQ(*intersections[0].object, s);
  ASSERT_TRUE(intersections[1].object);
  EXPECT_EQ(*intersections[1].object, s);
}

TEST(Ray, TranslatingARay) {
  const auto r1 = Ray(Point(1.0, 2.0, 3.0), Vector(0.0, 1.0, 0.0));
  const auto m = tf::translation(3.0, 4.0, 5.0);

  const auto r2 = r1.transform(m);
  EXPECT_EQ(r2.origin(), Point(4, 6, 8));
  EXPECT_EQ(r2.direction(), Vector(0, 1, 0));
}

TEST(Ray, ScalingARay) {
  const auto r1 = Ray(Point(1.0, 2.0, 3.0), Vector(0.0, 1.0, 0.0));
  const auto m = tf::scaling(2.0, 3.0, 4.0);

  const auto r2 = r1.transform(m);
  EXPECT_EQ(r2.origin(), Point(2.0, 6.0, 12.0));
  EXPECT_EQ(r2.direction(), Vector(0.0, 3.0, 0.0));
}