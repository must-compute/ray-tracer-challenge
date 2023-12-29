#include <gtest/gtest.h>

#include "../src/Matrix.h"

TEST(Matrix, FourByFourConstruction) {
  constexpr size_t w = 4;
  constexpr size_t h = 4;
  auto cells = std::array<std::array<double, w>, h>{
      {{1.0, 2.0, 3.0, 4.0}, {5.5, 6.5, 7.5, 8.5}, {9.0, 10.0, 11.0, 12.0}, {13.5, 14.5, 15.5, 16.5}}
  };
  auto m = Matrix<h, w>{cells};
  EXPECT_EQ(m.cells[0][0], 1.0);
  EXPECT_EQ(m.cells[0][3], 4.0);
  EXPECT_EQ(m.cells[1][0], 5.5);
  EXPECT_EQ(m.cells[1][2], 7.5);
  EXPECT_EQ(m.cells[2][2], 11.0);
  EXPECT_EQ(m.cells[3][0], 13.5);
  EXPECT_EQ(m.cells[3][2], 15.5);
}

TEST(Matrix, TwoByTwoConstruction) {
  constexpr size_t w = 2;
  constexpr size_t h = 2;
  auto cells = std::array<std::array<double, w>, h>{
      {{-3.0, 5.0}, {1.0, -2.0}}
  };
  auto m = Matrix<h, w>{cells};
  EXPECT_EQ(m.cells[0][0], -3.0);
  EXPECT_EQ(m.cells[0][1], 5.0);
  EXPECT_EQ(m.cells[1][0], 1.0);
  EXPECT_EQ(m.cells[1][1], -2.0);
}

TEST(Matrix, ThreeByThreeConstruction) {
  constexpr size_t w = 3;
  constexpr size_t h = 3;
  const auto cells = std::array<std::array<double, w>, h>{
      {{-3.0, 5.0, 0.0}, {1.0, -2.0, -7.0}, {0.0, 1.0, 1.0}}
  };
  const auto m = Matrix<h, w>{cells};
  EXPECT_EQ(m.cells[0][0], -3.0);
  EXPECT_EQ(m.cells[1][1], -2.0);
  EXPECT_EQ(m.cells[2][2], 1.0);
}

TEST(Matrix, ComparisonEqual) {
  constexpr size_t w = 4;
  constexpr size_t h = 4;
  const auto cells = std::array<std::array<double, w>, h>{
      {{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}, {9.0, 8.0, 7.0, 6.0}, {5.0, 4.0, 3.0, 2.0}}
  };
  const auto m1 = Matrix<h, w>{cells};
  const auto m2 = Matrix<h, w>{cells};
  EXPECT_TRUE(m1 == m2);
}

TEST(Matrix, ComparisonNotEqual) {
  constexpr size_t w = 4;
  constexpr size_t h = 4;
  auto cells = std::array<std::array<double, w>, h>{
      {{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}, {9.0, 8.0, 7.0, 6.0}, {5.0, 4.0, 3.0, 2.0}}
  };
  const auto m1 = Matrix<h, w>{cells};

  cells[2][3] = 42.0;
  const auto m2 = Matrix<h, w>{cells};
  EXPECT_TRUE(m1 != m2);
}

TEST(Matrix, ComparisonWithinEpsilon) {
  constexpr size_t w = 4;
  constexpr size_t h = 4;
  auto cells = std::array<std::array<double, w>, h>{
      {{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}, {9.0, 8.0, 7.0, 6.0}, {5.0, 4.0, 3.0, 2.0}}
  };
  const auto m1 = Matrix<h, w>{cells};
  auto m2 = Matrix<h, w>{cells};
  m2.cells[2][3] += EPSILON;
  EXPECT_TRUE(m1 == m2);
  m2.cells[2][3] += EPSILON;
  EXPECT_TRUE(m1 != m2);
}

TEST(Matrix, Multiplication) {
  constexpr size_t w = 4;
  constexpr size_t h = 4;
  const auto m1 = Matrix<h, w>{std::array<std::array<double, w>, h>{
      {{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}, {9.0, 8.0, 7.0, 6.0}, {5.0, 4.0, 3.0, 2.0}}
  }};
  const auto m2 = Matrix<h, w>{std::array<std::array<double, w>, h>{
      {{-2.0, 1.0, 2.0, 3.0}, {3.0, 2.0, 1.0, -1.0}, {4.0, 3.0, 6.0, 5.0}, {1.0, 2.0, 7.0, 8.0}}
  }};

  const auto expected_m = Matrix<h, w>{std::array<std::array<double, w>, h>{
      {{20.0, 22.0, 50.0, 48.0}, {44.0, 54.0, 114.0, 108.0}, {40.0, 58.0, 110.0, 102.0}, {16.0, 26.0, 46.0, 42.0}}
  }};

  EXPECT_EQ(m1 * m2, expected_m);
}

TEST(Matrix, MulTuple) {
  constexpr size_t w = 4;
  constexpr size_t h = 4;
  const auto m = Matrix<h, w>{std::array<std::array<double, w>, h>{
      {{1.0, 2.0, 3.0, 4.0}, {2.0, 4.0, 4.0, 2.0}, {8.0, 6.0, 4.0, 1.0}, {0.0, 0.0, 0.0, 1.0}}
  }};
  const auto t = Tuple(1.0, 2.0, 3.0, 1.0);

  const auto expected_tuple = Tuple(18.0, 24.0, 33.0, 1.0);

  EXPECT_EQ(m * t, expected_tuple);
}

TEST(Matrix, IdentityMultiply) {
  constexpr size_t w = 4;
  constexpr size_t h = 4;
  const auto m = Matrix<h, w>{std::array<std::array<double, w>, h>{
      {{1.0, 2.0, 3.0, 4.0}, {2.0, 4.0, 4.0, 2.0}, {8.0, 6.0, 4.0, 1.0}, {0.0, 0.0, 0.0, 1.0}}
  }};
  const auto identity = Matrix<h, w>::identity();

  EXPECT_EQ(m * identity, m);
}

TEST(Matrix, Transpose) {
  constexpr size_t w = 4;
  constexpr size_t h = 4;
  const auto m = Matrix<h, w>{std::array<std::array<double, w>, h>{
      {{0.0, 9.0, 3.0, 0.0},
       {9.0, 8.0, 0.0, 8.0},
       {1.0, 8.0, 5.0, 3.0},
       {0.0, 0.0, 5.0, 8.0}}
  }};
  const auto expected = Matrix<h, w>{std::array<std::array<double, w>, h>{
      {{0.0, 9.0, 1.0, 0.0},
       {9.0, 8.0, 8.0, 0.0},
       {3.0, 0.0, 5.0, 5.0},
       {0.0, 8.0, 3.0, 8.0}}
  }};

  EXPECT_EQ(m.transpose(), expected);
}

TEST(Matrix, TransposeIdentity) {
  constexpr size_t w = 4;
  constexpr size_t h = 4;
  const auto identity = Matrix<h, w>::identity();
  EXPECT_EQ(identity.transpose(), identity);
}

TEST(Matrix, Determinant) {
  constexpr size_t w = 2;
  constexpr size_t h = 2;
  const auto m = Matrix<h, w>{std::array<std::array<double, w>, h>{
      {{1.0, 5.0},
       {-3.0, 2.0}}
  }};
  const double expected = 17.0;
  EXPECT_EQ(m.determinant(), expected);
}

TEST(Matrix, Submatrix) {
  {
    constexpr size_t w = 3;
    constexpr size_t h = 3;
    const auto m = Matrix<h, w>{std::array<std::array<double, w>, h>{
        {{1.0, 5.0, 0.0},
         {-3.0, 2.0, 7.0},
         {0.0, 6.0, -3.0}}
    }};
    const auto expected = Matrix<h - 1, w - 1>{std::array<std::array<double, w - 1>, h - 1>{
        {{-3.0, 2.0},
         {0.0, 6.0}}
    }};
    EXPECT_EQ(m.submatrix(0, 2), expected);
  }

  {
    constexpr size_t w = 4;
    constexpr size_t h = 4;
    const auto m = Matrix<h, w>{std::array<std::array<double, w>, h>{
        {{1.0, 5.0, 0.0, 4.2},
         {-3.0, 2.0, 7.0, 6.9},
         {0.0, 6.0, -3.0, -6.66},
         {1.0, 3.0, -2.0, -8.0}}
    }};
    const auto expected = Matrix<h - 1, w - 1>{std::array<std::array<double, w - 1>, h - 1>{
        {{1.0, 0.0, 4.2},
         {-3.0, 7.0, 6.9},
         {1.0, -2.0, -8.0}}
    }};
    EXPECT_EQ(m.submatrix(2, 1), expected);
  }
}

TEST(Matrix, Minor) {
  constexpr size_t w = 3;
  constexpr size_t h = 3;
  const auto m = Matrix<h, w>{std::array<std::array<double, w>, h>{
      {{3.0, 5.0, 0.0},
       {2.0, -1.0, -7.0},
       {6.0, -1.0, 5.0}}
  }};
  const auto b = m.submatrix(1, 0);
  EXPECT_EQ(b.determinant(), 25);
  EXPECT_EQ(m.minor(1, 0), 25);
}

TEST(Matrix, Cofactor) {
  constexpr size_t w = 3;
  constexpr size_t h = 3;
  const auto m = Matrix<h, w>{std::array<std::array<double, w>, h>{
      {{3.0, 5.0, 0.0},
       {2.0, -1.0, -7.0},
       {6.0, -1.0, 5.0}}
  }};
  EXPECT_EQ(m.minor(0, 0), -12.0);
  EXPECT_EQ(m.cofactor(0, 0), -12.0);
  EXPECT_EQ(m.minor(1, 0), 25.0);
  EXPECT_EQ(m.cofactor(1, 0), -25.0);
}

TEST(Matrix, DeterminantThreeByThree) {
  constexpr size_t w = 3;
  constexpr size_t h = 3;
  const auto m = Matrix<h, w>{std::array<std::array<double, w>, h>{
      {{1.0, 2.0, 6.0},
       {-5.0, 8.0, -4.0},
       {2.0, 6.0, 4.0}}
  }};
  EXPECT_EQ(m.cofactor(0, 0), 56.0);
  EXPECT_EQ(m.cofactor(0, 1), 12.0);
  EXPECT_EQ(m.cofactor(0, 2), -46.0);
  EXPECT_EQ(m.determinant(), -196.0);
}

TEST(Matrix, DeterminantFourByFour) {
  constexpr size_t w = 4;
  constexpr size_t h = 4;
  const auto m = Matrix<h, w>{std::array<std::array<double, w>, h>{
      {{-2.0, -8.0, 3.0, 5.0},
       {-3.0, 1.0, 7.0, 3.0},
       {1.0, 2.0, -9.0, 6.0},
       {-6.0, 7.0, 7.0, -9.0}}
  }};
  EXPECT_EQ(m.cofactor(0, 0), 690.0);
  EXPECT_EQ(m.cofactor(0, 1), 447.0);
  EXPECT_EQ(m.cofactor(0, 2), 210.0);
  EXPECT_EQ(m.cofactor(0, 3), 51.0);
  EXPECT_EQ(m.determinant(), -4071.0);
}

TEST(Matrix, IsInvertible) {
  constexpr size_t w = 4;
  constexpr size_t h = 4;
  const auto invertible = Matrix<h, w>{std::array<std::array<double, w>, h>{
      {{6.0, 4.0, 4.0, 4.0},
       {5.0, 5.0, 7.0, 6.0},
       {4.0, -9.0, 3.0, -7.0},
       {9.0, 1.0, 7.0, -6.0}}
  }};
  EXPECT_EQ(invertible.determinant(), -2120.0);
  EXPECT_TRUE(invertible.is_invertible());

  const auto not_invertible = Matrix<h, w>{std::array<std::array<double, w>, h>{
      {{-4.0, 2.0, -2.0, -3.0},
       {9.0, 6.0, 2.0, 6.0},
       {0.0, -5.0, 1.0, -5.0},
       {0.0, 0.0, 0.0, 0.0}}
  }};
  EXPECT_EQ(not_invertible.determinant(), 0.0);
  EXPECT_FALSE(not_invertible.is_invertible());
}

TEST(Matrix, Inverse) {
  {
    constexpr size_t w = 4;
    constexpr size_t h = 4;
    const auto m = Matrix<h, w>{std::array<std::array<double, w>, h>{
        {{-5.0, 2.0, 6.0, -8.0},
         {1.0, -5.0, 1.0, 8.0},
         {7.0, 7.0, -6.0, -7.0},
         {1.0, -3.0, 7.0, 4.0}}
    }};
    const auto m_inverse = m.inverse();
    const auto expected_inverse = Matrix<h, w>{std::array<std::array<double, w>, h>{
        {{0.21805, 0.45113, 0.24060, -0.04511},
         {-0.80827, -1.45677, -0.44361, 0.52068},
         {-0.07895, -0.22368, -0.05263, 0.19737},
         {-0.52256, -0.81391, -0.30075, 0.30639}}
    }};

    EXPECT_EQ(m.determinant(), 532.0);
    EXPECT_EQ(m.cofactor(2, 3), -160.0);
    EXPECT_TRUE(within_epsilon(m_inverse.cells[3][2], -160.0 / 532.0));
    EXPECT_EQ(m.cofactor(3, 2), 105.0);
    EXPECT_TRUE(within_epsilon(m_inverse.cells[2][3], 105.0 / 532.0));
    EXPECT_EQ(m_inverse, expected_inverse);
  }
  {
    constexpr size_t w = 4;
    constexpr size_t h = 4;
    const auto m = Matrix<h, w>{std::array<std::array<double, w>, h>{
        {{8.0, -5.0, 9.0, 2.0},
         {7.0, 5.0, 6.0, 1.0},
         {-6.0, 0.0, 9.0, 6.0},
         {-3.0, 0.0, -9.0, -4.0}}
    }};
    const auto m_inverse = m.inverse();
    const auto expected_inverse = Matrix<h, w>{std::array<std::array<double, w>, h>{
        {{-0.15385, -0.15385, -0.28205, -0.53846},
         {-0.07692, 0.12308, 0.02564, 0.03077},
         {0.35897, 0.35897, 0.43590, 0.92308},
         {-0.69231, -0.69231, -0.76923, -1.92308}}
    }};

    EXPECT_EQ(m_inverse, expected_inverse);
  }
  {
    constexpr size_t w = 4;
    constexpr size_t h = 4;
    const auto m = Matrix<h, w>{std::array<std::array<double, w>, h>{
        {{9.0, 3.0, 0.0, 9.0},
         {-5.0, -2.0, -6.0, -3.0},
         {-4.0, 9.0, 6.0, 4.0},
         {-7.0, 6.0, 6.0, 2.0}}
    }};
    const auto m_inverse = m.inverse();
    const auto expected_inverse = Matrix<h, w>{std::array<std::array<double, w>, h>{
        {{-0.04074, -0.07778, 0.14444, -0.22222},
         {-0.07778, 0.03333, 0.36667, -0.33333},
         {-0.02901, -0.14630, -0.10926, 0.12963},
         {0.17778, 0.06667, -0.26667, 0.33333}}
    }};

    EXPECT_EQ(m_inverse, expected_inverse);
  }
}

TEST(Matrix, InverseMultiply) {
  constexpr size_t w = 4;
  constexpr size_t h = 4;
  const auto A = Matrix<h, w>{std::array<std::array<double, w>, h>{
      {{3.0, -9.0, 7.0, 3.0},
       {3.0, -8.0, 2.0, -9.0},
       {-4.0, 4.0, 4.0, 1.0},
       {-6.0, 5.0, -1.0, 1.0}}
  }};
  const auto B = Matrix<h, w>{std::array<std::array<double, w>, h>{
      {{8.0, 2.0, 2.0, 2.0},
       {3.0, -1.0, 7.0, 0.0},
       {7.0, 0.0, 5.0, 4.0},
       {6.0, -2.0, 0.0, 5.0}}
  }};
  const auto C = A * B;
  EXPECT_EQ(C * B.inverse(), A);
}

