#include "GradientPattern.h"

Color GradientPattern::pattern_at(const Tuple &point) const {
    const auto distance = b_ - a_;
    const auto fraction = point.x() - std::floor(point.x());
    return a_ + distance * fraction;
}

GradientPattern::GradientPattern(const Color &a, const Color &b) : Pattern(a, b) {}
