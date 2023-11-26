#include "StripePattern.h"
#include "Shape.h"


StripePattern::StripePattern() : StripePattern{Color{}, Color{}} {}

StripePattern::StripePattern(const Color &a, const Color &b) : a_{a}, b_{b}, transform_{tf::Transform::identity()} {}

Color StripePattern::a() const {
    return a_;
}

Color StripePattern::b() const {
    return b_;
}

tf::Transform StripePattern::transform() const {
    return transform_;
}

void StripePattern::set_transform(const tf::Transform &t) {
    transform_ = t;
}

Color StripePattern::stripe_at(const Tuple &point) const {
    return static_cast<int>(std::floor(point.x())) % 2 == 0 ? a_ : b_;
}

Color StripePattern::stripe_at_object(const Shape &object, const Tuple &world_point) const {
    const auto object_point = object.transform().inverse() * world_point;
    const auto pattern_point = transform_.inverse() * object_point;
    return stripe_at(pattern_point);
}