#include <gtest/gtest.h>
#include "Color.h"
#include "StripePattern.h"
#include "GradientPattern.h"
#include "RingPattern.h"
#include "TestPattern.h"
#include "CheckerPattern.h"
#include "Tuple.h"
#include "Sphere.h"

class PatternFixture : public ::testing::Test {
protected:
  const Color black = Color{0.0, 0.0, 0.0};
  const Color white = Color{1.0, 1.0, 1.0};
};

TEST_F(PatternFixture, CreateStripePattern) {
  const auto pattern = StripePattern{white, black};
  EXPECT_EQ(pattern.a(), white);
  EXPECT_EQ(pattern.b(), black);
}

TEST_F(PatternFixture, StripePatternAlternatesInX) {
  const auto pattern = StripePattern{white, black};
  EXPECT_EQ(pattern.pattern_at(Point(0.0, 0.0, 0.0)), white);
  EXPECT_EQ(pattern.pattern_at(Point(0.9, 0.0, 0.0)), white);
  EXPECT_EQ(pattern.pattern_at(Point(1.0, 0.0, 0.0)), black);
  EXPECT_EQ(pattern.pattern_at(Point(-0.1, 0.0, 0.0)), black);
  EXPECT_EQ(pattern.pattern_at(Point(-1.0, 0.0, 0.0)), black);
  EXPECT_EQ(pattern.pattern_at(Point(-1.1, 0.0, 0.0)), white);
}

TEST_F(PatternFixture, StripePatternIsConstantInY) {
  const auto pattern = StripePattern{white, black};
  EXPECT_EQ(pattern.pattern_at(Point(0.0, 0.0, 0.0)), white);
  EXPECT_EQ(pattern.pattern_at(Point(0.0, 1.0, 0.0)), white);
  EXPECT_EQ(pattern.pattern_at(Point(0.0, 2.0, 0.0)), white);
}

TEST_F(PatternFixture, StripePatternIsConstantInZ) {
  const auto pattern = StripePattern{white, black};
  EXPECT_EQ(pattern.pattern_at(Point(0.0, 0.0, 1.0)), white);
  EXPECT_EQ(pattern.pattern_at(Point(0.0, 0.0, 1.0)), white);
  EXPECT_EQ(pattern.pattern_at(Point(0.0, 0.0, 2.0)), white);
}

TEST_F(PatternFixture, StripesWithObjectTransformation) {
  auto object = Sphere{};
  object.set_transform(tf::scaling(2.0, 2.0, 2.0));

  const auto pattern = StripePattern{white, black};

  EXPECT_EQ(pattern.pattern_at_shape(object, Point(1.5, 0.0, 0.0)), white);
}

TEST_F(PatternFixture, StripesWithPatternTransformation) {
  const auto object = Sphere{};

  auto pattern = StripePattern{white, black};
  pattern.set_transform(tf::scaling(2.0, 2.0, 2.0));

  EXPECT_EQ(pattern.pattern_at_shape(object, Point(1.5, 0.0, 0.0)), white);
}

TEST_F(PatternFixture, StripesWithBothObjectAndPatternTransformation) {
  auto object = Sphere{};
  object.set_transform(tf::scaling(2.0, 2.0, 2.0));

  auto pattern = StripePattern{white, black};
  pattern.set_transform(tf::translation(0.5, 0.0, 0.0));

  EXPECT_EQ(pattern.pattern_at_shape(object, Point(2.5, 0.0, 0.0)), white);
}

TEST_F(PatternFixture, PatternWithObjectTransformation) {
  auto object = Sphere{};
  object.set_transform(tf::scaling(2.0, 2.0, 2.0));

  const auto pattern = TestPattern{};

  EXPECT_EQ(pattern.pattern_at_shape(object, Point(2.0, 3.0, 4.0)), (Color{1.0, 1.5, 2.0}));
}

TEST_F(PatternFixture, PatternWithPatternTransformation) {
  const auto object = Sphere{};

  auto pattern = TestPattern{};
  pattern.set_transform(tf::scaling(2.0, 2.0, 2.0));

  EXPECT_EQ(pattern.pattern_at_shape(object, Point(2.0, 3.0, 4.0)), (Color{1.0, 1.5, 2.0}));
}

TEST_F(PatternFixture, PatternWithObjectAndPatternTransformation) {
  auto object = Sphere{};
  object.set_transform(tf::scaling(2.0, 2.0, 2.0));

  auto pattern = TestPattern{};
  pattern.set_transform(tf::translation(0.5, 1.0, 1.5));

  EXPECT_EQ(pattern.pattern_at_shape(object, Point(2.5, 3.0, 3.5)), (Color{0.75, 0.5, 0.25}));
}

TEST_F(PatternFixture, GradientLinearlyInterpolatesBetweenColors) {
  auto pattern = GradientPattern{white, black};

  EXPECT_EQ(pattern.pattern_at(Point(0.0, 0.0, 0.0)), white);
  EXPECT_EQ(pattern.pattern_at(Point(0.25, 0.0, 0.0)), (Color{0.75, 0.75, 0.75}));
  EXPECT_EQ(pattern.pattern_at(Point(0.5, 0.0, 0.0)), (Color{0.5, 0.5, 0.5}));
  EXPECT_EQ(pattern.pattern_at(Point(0.75, 0.0, 0.0)), (Color{0.25, 0.25, 0.25}));
}

TEST_F(PatternFixture, RingGradientShouldExtendInBothXAndZ) {
  auto pattern = RingPattern{white, black};

  EXPECT_EQ(pattern.pattern_at(Point(0.0, 0.0, 0.0)), white);
  EXPECT_EQ(pattern.pattern_at(Point(1.0, 0.0, 0.0)), black);
  EXPECT_EQ(pattern.pattern_at(Point(0.0, 0.0, 1.0)), black);
  EXPECT_EQ(pattern.pattern_at(Point(0.708, 0.0, 0.708)), black); // Slightly more than sqrt(2)/2
}

TEST_F(PatternFixture, CheckerGradientShouldRepeatInX) {
  auto pattern = CheckerPattern{white, black};

  EXPECT_EQ(pattern.pattern_at(Point(0.0, 0.0, 0.0)), white);
  EXPECT_EQ(pattern.pattern_at(Point(0.99, 0.0, 0.0)), white);
  EXPECT_EQ(pattern.pattern_at(Point(1.01, 0.0, 0.0)), black);
}

TEST_F(PatternFixture, CheckerGradientShouldRepeatInY) {
  auto pattern = CheckerPattern{white, black};

  EXPECT_EQ(pattern.pattern_at(Point(0.0, 0.0, 0.0)), white);
  EXPECT_EQ(pattern.pattern_at(Point(0.0, 0.99, 0.0)), white);
  EXPECT_EQ(pattern.pattern_at(Point(0.0, 1.01, 0.0)), black);
}

TEST_F(PatternFixture, CheckerGradientShouldRepeatInZ) {
  auto pattern = CheckerPattern{white, black};

  EXPECT_EQ(pattern.pattern_at(Point(0.0, 0.0, 0.0)), white);
  EXPECT_EQ(pattern.pattern_at(Point(0.0, 0.0, 0.99)), white);
  EXPECT_EQ(pattern.pattern_at(Point(0.0, 0.0, 1.01)), black);
}
