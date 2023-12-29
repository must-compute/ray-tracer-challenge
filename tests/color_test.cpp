#include <gtest/gtest.h>

#include "Color.h"

TEST(Color, Basic) {
  const Color c1{-0.5, 0.4, 1.7};
  EXPECT_EQ(c1.red(), -0.5);
  EXPECT_EQ(c1.green(), 0.4);
  EXPECT_EQ(c1.blue(), 1.7);
}

TEST(Color, Addition) {
  const Color c1{3.0, -2.0, 5.0};
  const Color c2{-2.0, 3.0, 1.0};

  EXPECT_EQ(c1 + c2, (Color{1.0, 1.0, 6.0}));
}

TEST(Color, Subtraction) {
  {
    const Color c1{3.0, 2.0, 1.0};
    const Color c2{5.0, 6.0, 7.0};
    EXPECT_EQ(c1 - c2, (Color{-2.0, -4.0, -6.0}));
  }
  {
    const Color c1{0.0, 0.0, 0.0};
    const Color c2{5.0, 6.0, 7.0};
    EXPECT_EQ(c1 - c2, (Color{-5.0, -6.0, -7.0}));
  }
}

TEST(Color, ScalarMultiply) {
  const Color c{1.0, -2.0, 3.0};
  EXPECT_EQ(c * 3.5, (Color{3.5, -7.0, 10.5}));
}

TEST(Color, ElementWiseProduct) {
  const Color c1{1.0, 0.2, 0.4};
  const Color c2{0.9, 1.0, 0.1};
  EXPECT_EQ(c1 * c2, (Color{0.9, 0.2, 0.04}));
}
