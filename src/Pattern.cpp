#include "Pattern.h"

#include "Shape.h"

Pattern::Pattern() : Pattern{Color{}, Color{}} {}

Pattern::Pattern(const Color &a, const Color &b) : a_{a}, b_{b}, transform_{tf::Transform::identity()} {}

Color Pattern::a() const {
    return a_;
}

Color Pattern::b() const {
    return b_;
}

tf::Transform Pattern::transform() const {
    return transform_;
}

void Pattern::set_transform(const tf::Transform &t) {
    transform_ = t;
}

Color Pattern::pattern_at_shape(const Shape &object, const Tuple &world_point) const {
    const auto object_point = object.transform().inverse() * world_point;
    const auto pattern_point = transform_.inverse() * object_point;
    return pattern_at(pattern_point);
}