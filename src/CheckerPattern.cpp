#include "CheckerPattern.h"

#include <cmath>

CheckerPattern::CheckerPattern(const Color &a, const Color &b) : Pattern(a, b) {}

Color CheckerPattern::pattern_at(const Tuple &point) const {
    return static_cast<int>(std::floor(point.x()) + std::floor(point.y()) + std::floor(point.z())) % 2 == 0 ? a_ : b_;
}
