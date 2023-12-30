#include "StripePattern.h"
#include "Shape.h"

StripePattern::StripePattern(const Color &a, const Color &b) : Pattern{a, b} {}

Color StripePattern::pattern_at(const Point &point) const {
  return static_cast<int>(std::floor(point.x())) % 2 == 0 ? a_ : b_;
}