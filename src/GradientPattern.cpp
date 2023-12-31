#include "GradientPattern.h"

GradientPattern::GradientPattern(const Color &a, const Color &b) : Pattern(a, b) {}

Color GradientPattern::pattern_at(const Point &point) const {
  const auto distance = b_ - a_;
  const auto fraction = point.x() - std::floor(point.x());
  return a_ + distance * fraction;
}