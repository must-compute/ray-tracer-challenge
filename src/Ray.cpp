
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

/*
Intersections Ray::intersect(const Sphere &sphere) const {

    const auto transformed_ray = this->transform(sphere.transform().inverse());
    const auto sphere_to_ray = transformed_ray.origin_ - make_point(0.0, 0.0, 0.0);

    const auto a = transformed_ray.direction_.dot(transformed_ray.direction_);
    const auto b = 2 * transformed_ray.direction_.dot(sphere_to_ray);
    const auto c = sphere_to_ray.dot(sphere_to_ray) - 1.0;

    const auto discriminant = (b * b) - 4 * (a * c);

    if (discriminant < 0.0) {
        // MISS!
        return {};
    }

    const auto discr_sqrt = std::sqrt(discriminant);
    const auto t1 = (-b - discr_sqrt) / (2 * a);
    const auto t2 = (-b + discr_sqrt) / (2 * a);

    // NOTE: we care about the order of intersections (in ascending order of t).
    if (t1 > t2) {
        return {Intersection{t2, sphere}, Intersection{t1, sphere}};
    }
    return {Intersection{t1, sphere}, Intersection{t2, sphere}};
}
 */

Tuple Ray::origin() const {
    return origin_;
}

Tuple Ray::direction() const {
    return direction_;
}

Ray Ray::transform(const tf::Transform &m) const {
    return {m * origin_, m * direction_};
}
