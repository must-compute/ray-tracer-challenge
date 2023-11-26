#include "StripePattern.h"


StripePattern::StripePattern() : StripePattern{Color{}, Color{}} {}

StripePattern::StripePattern(const Color &a, const Color &b) : a_{a}, b_{b} {}

Color StripePattern::a() const {
    return a_;
}

Color StripePattern::b() const {
    return b_;
}

Color StripePattern::stripe_at(const Tuple &point) const {
    return static_cast<int>(std::floor(point.x())) % 2 == 0 ? a_ : b_;
}
