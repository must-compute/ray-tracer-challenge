#include "RingPattern.h"

#include <cmath>

RingPattern::RingPattern(const Color &a, const Color &b) : Pattern(a, b) {}

Color RingPattern::pattern_at(const Tuple &point) const {
  const auto distance = std::sqrt(point.x() * point.x() + point.z() * point.z());
  return static_cast<int>(std::floor(distance)) % 2 == 0 ? a_ : b_;
}
