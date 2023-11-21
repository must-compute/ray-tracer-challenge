
#include "Ray.h"

Ray::Ray() : origin_(make_point(0.0, 0.0, 0.0)), direction_(make_vector(0.0, 0.0, 0.0)) {}

Ray::Ray(const Tuple &origin_in, const Tuple &direction_in) : origin_(origin_in), direction_(direction_in) {
    // TODO see if these asserts are ignored in release mode to reduce overhead.
    assert(origin_.is_point());
    assert(direction_.is_vector());
}

Tuple Ray::position_at_t(double t) const {
    return origin_ + direction_ * t;
}

std::vector<double> Ray::intersect(const Sphere &sphere) const {
    std::vector<double> intersections;
    // TODO implement
    return intersections;
}

Tuple Ray::origin() const {
    return origin_;
}

Tuple Ray::direction() const {
    return direction_;
}
