#include <gtest/gtest.h>

#include "SmoothTriangle.h"
#include "Tuple.h"

class SmoothTriangleFixture : public ::testing::Test {
protected:
  SmoothTriangleFixture() :
      p1{make_point(0.0, 1.0, 0.0)},
      p2{make_point(-1.0, 0.0, 0.0)},
      p3{make_point(1.0, 0.0, 0.0)},
      n1{make_vector(0.0, 1.0, 0.0)},
      n2{make_vector(-1.0, 0.0, 0.0)},
      n3{make_vector(1.0, 0.0, 0.0)},
      tri{SmoothTriangle{p1, p2, p3, n1, n2, n3}} {}

  const Point p1;
  const Point p2;
  const Point p3;
  const Vector n1;
  const Vector n2;
  const Vector n3;
  SmoothTriangle tri;
};

TEST_F(SmoothTriangleFixture, ConstructingSmoothTriangle) {
  EXPECT_EQ(tri.p1(), p1);
  EXPECT_EQ(tri.p2(), p2);
  EXPECT_EQ(tri.p3(), p3);
  EXPECT_EQ(tri.n1(), n1);
  EXPECT_EQ(tri.n2(), n2);
  EXPECT_EQ(tri.n3(), n3);
}

TEST_F(SmoothTriangleFixture, IntersectionWithSmoothTriangleStoresUAndV) {
  const auto ray = Ray{make_point(-0.2, 0.3, -2.0), make_vector(0.0, 0.0, 1.0)};
  const auto xs = tri.local_intersect(ray);
  ASSERT_EQ(xs.size(), 1);
  ASSERT_TRUE(xs[0].u);
  ASSERT_TRUE(xs[0].v);
  EXPECT_TRUE(within_epsilon(*xs[0].u, 0.45));
  EXPECT_TRUE(within_epsilon(*xs[0].v, 0.25));
}

TEST_F(SmoothTriangleFixture, SmoothTriangleUsesUAndVToInterpolateNormal) {
  const auto i = Intersection{1.0, &tri, 0.45, 0.25};
  const auto normal = tri.normal_at(make_point(0.0, 0.0, 0.0), i);
  EXPECT_EQ(normal, make_vector(-0.5547, 0.83205, 0.0));
}

TEST_F(SmoothTriangleFixture, PreparingNormalOnSmoothTriangle) {
  const auto i = Intersection{1.0, &tri, 0.45, 0.25};
  const auto ray = Ray{make_point(-0.2, 0.3, -2.0), make_vector(0.0, 0.0, 1.0)};
  const auto comps = i.prepare_computations(ray, Intersections{i});
  EXPECT_EQ(comps.normalv, make_vector(-0.5547, 0.83205, 0.0));
}