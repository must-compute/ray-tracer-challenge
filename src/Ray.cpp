
#include "Ray.h"

Ray::Ray() : origin(make_point(0.0, 0.0, 0.0)), direction(make_vector(0.0, 0.0, 0.0)) {}

Ray::Ray(const Tuple &origin_in, const Tuple &direction_in) : origin(origin_in), direction(direction_in) {
    // TODO see if these asserts are ignored in release mode to reduce overhead.
    assert(origin.is_point());
    assert(direction.is_vector());
}

Tuple Ray::position_at_t(double t) const {
    return origin + direction * t;
}

std::vector<double> Ray::intersect(const Sphere &sphere) const {
    std::vector<double> intersections;
    // TODO implement
    return intersections;
}
