#include "Plane.h"

Tuple Plane::local_normal_at(const Tuple &point_in_object_space, const std::optional<Intersection> &intersection) const {
    return make_vector(0.0, 1.0, 0.0);
}


[[nodiscard]] Intersections Plane::local_intersect(const Ray &ray) {
    // Parallel case (no intersection) and coplanar case (infinite intersections).
    if (std::abs(ray.direction().y()) < EPSILON) {
        return {};
    }

    const auto t = -ray.origin().y() / ray.direction().y();

    return {Intersection{t, this}};
}

BoundingBox Plane::make_bounding_box() const {
    return {make_point(-std::numeric_limits<double>::infinity(), 0.0, -std::numeric_limits<double>::infinity()),
            make_point(std::numeric_limits<double>::infinity(), 0.0, std::numeric_limits<double>::infinity())
    };
}
