#include "Cylinder.h"

Tuple Cylinder::local_normal_at(const Tuple &point_in_object_space) const {
    return {};
}


[[nodiscard]] Intersections Cylinder::local_intersect(const Ray &ray) {
    const auto a = std::pow(ray.direction().x(), 2) + std::pow(ray.direction().z(), 2);

    // Ray is parallel to the y axis.
    if (std::abs(a) < EPSILON) {
        return {};
    }

    const auto b = 2 * ray.origin().x() * ray.direction().x() +
                   2 * ray.origin().z() * ray.direction().z();
    const auto c = std::pow(ray.origin().x(), 2) + std::pow(ray.origin().z(), 2) - 1.0;

    const auto discriminant = std::pow(b, 2) - 4 * a * c;

    // Ray does not intersect the cylinder
    if (discriminant < 0) {
        return {};
    }

    const auto t0 = (-b - std::sqrt(discriminant)) / (2 * a);
    const auto t1 = (-b + std::sqrt(discriminant)) / (2 * a);
    const auto cylinder = std::make_shared<Cylinder>(*this);
    return {Intersection{t0, cylinder}, Intersection{t1, cylinder}};
}
