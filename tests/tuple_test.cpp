#include <gtest/gtest.h>

#include "../src/Tuple.h"

TEST(Tuple, Basic) {
  double x, y, z, w;
  x = 1.0;
  y = 2.2;
  z = 3.5;
  w = 1.0;
  const Point p{x, y, z};
  EXPECT_EQ(p.x(), x);
  EXPECT_EQ(p.y(), y);
  EXPECT_EQ(p.z(), z);
  EXPECT_EQ(p.w(), w);
}

TEST(Tuple, Addition) {
  const Point point{3.0, -2.0, 5.0};
  const Vector vector{-2.0, 3.0, 1.0};

  EXPECT_EQ(point + vector, (Point{1.0, 1.0, 6.0}));
}

TEST(Tuple, Subtraction) {
  {
    const Point p1 = Point(3.0, 2.0, 1.0);
    const Point p2 = Point(5.0, 6.0, 7.0);
    EXPECT_EQ(p1 - p2, Vector(-2.0, -4.0, -6.0));
  }
  {
    const Point p1 = Point(3.0, 2.0, 1.0);
    const Vector v1 = Vector(5.0, 6.0, 7.0);
    EXPECT_EQ(p1 - v1, Point(-2.0, -4.0, -6.0));
  }
  {
    const Vector v1 = Vector(3.0, 2.0, 1.0);
    const Vector v2 = Vector(5.0, 6.0, 7.0);
    EXPECT_EQ(v1 - v2, Vector(-2.0, -4.0, -6.0));
  }
  {
    const Vector v1 = Vector(0.0, 0.0, 0.0);
    const Vector v2 = Vector(5.0, 6.0, 7.0);
    EXPECT_EQ(v1 - v2, Vector(-5.0, -6.0, -7.0));
  }
}

TEST(Tuple, Negation) {
  {
    const Vector t1 = Vector(1.0, 2.0, 3.0);
    EXPECT_EQ(-t1, Vector(-1.0, -2.0, -3.0));
  }
  {
    const Point t1 = Point(1.0, 2.0, 3.0);
    EXPECT_NE(-t1, Point(-1.0, -2.0, -3.0));
  }
}

TEST(Tuple, ScalarMultiply) {
  {
    const Vector t = Vector(1.0, -2.0, 3.0);
    EXPECT_EQ(t * 3.5, Vector(3.5, -7.0, 10.5));
  }
  {
    const Vector t = Vector(1.0, -2.0, 3.0);
    EXPECT_EQ(t * 0.5, Vector(0.5, -1.0, 1.5));
  }
}

TEST(Tuple, ScalarDivide) {
  const Vector t = Vector(1.0, -2.0, 3.0);
  EXPECT_EQ(t / 2.0, Vector(0.5, -1.0, 1.5));
}

TEST(Tuple, Magnitude) {
  {
    const Vector v = Vector(1.0, 0.0, 0.0);
    EXPECT_EQ(v.magnitude(), 1.0);
  }
  {
    const Vector v = Vector(0.0, 1.0, 0.0);
    EXPECT_EQ(v.magnitude(), 1.0);
  }
  {
    const Vector v = Vector(0.0, 0.0, 1.0);
    EXPECT_EQ(v.magnitude(), 1.0);
  }
  {
    const Vector v = Vector(1.0, 2.0, 3.0);
    EXPECT_TRUE(within_epsilon(v.magnitude(), std::sqrt(14.0)));
  }
  {
    const Vector v = Vector(-1.0, -2.0, -3.0);
    EXPECT_TRUE(within_epsilon(v.magnitude(), std::sqrt(14.0)));
  }
}

TEST(Tuple, Normalize) {
  {
    const Vector v = Vector(4.0, 0.0, 0.0);
    EXPECT_EQ(v.normalize(), Vector(1.0, 0.0, 0.0));
  }
  {
    const Vector v = Vector(1.0, 2.0, 3.0);
    const double sqrt_of_fourteen = std::sqrt(14.0);
    EXPECT_EQ(v.normalize(), Vector(1.0 / sqrt_of_fourteen, 2.0 / sqrt_of_fourteen, 3.0 / sqrt_of_fourteen));
  }
  {
    const Vector v = Vector(1.0, 2.0, 3.0);
    EXPECT_TRUE(within_epsilon(v.normalize().magnitude(), 1.0));
  }
}

TEST(Tuple, DotProduct) {
  const Vector v1 = Vector(1.0, 2.0, 3.0);
  const Vector v2 = Vector(2.0, 3.0, 4.0);
  EXPECT_EQ(v1.dot(v2), 20.0);
}

TEST(Tuple, CrossProduct) {
  const Vector v1 = Vector(1.0, 2.0, 3.0);
  const Vector v2 = Vector(2.0, 3.0, 4.0);
  const Vector expected = Vector(-1.0, 2.0, -1.0);
  EXPECT_EQ(v1.cross(v2), expected);
  EXPECT_EQ(v2.cross(v1), -expected);
}
