
#include "Sphere.h"
#include "Tuple.h"
#include "Ray.h"

#include <memory>

Tuple Sphere::local_normal_at(const Tuple &point_in_object_space) const {
    const auto normal_in_object_space = point_in_object_space - make_point(0.0, 0.0, 0.0);
}


[[nodiscard]] Intersections Sphere::local_intersect(const Ray &ray) {
    const auto transformed_ray = ray.transform(transform_.inverse());
    const auto sphere_to_ray = transformed_ray.origin() - make_point(0.0, 0.0, 0.0);

    const auto a = transformed_ray.direction().dot(transformed_ray.direction());
    const auto b = 2 * transformed_ray.direction().dot(sphere_to_ray);
    const auto c = sphere_to_ray.dot(sphere_to_ray) - 1.0;

    const auto discriminant = (b * b) - 4 * (a * c);

    if (discriminant < 0.0) {
        // MISS!
        return {};
    }

    const auto discr_sqrt = std::sqrt(discriminant);
    const auto t1 = (-b - discr_sqrt) / (2 * a);
    const auto t2 = (-b + discr_sqrt) / (2 * a);

    const auto copy = std::make_shared<Sphere>(*this);
    // NOTE: we care about the order of intersections (in ascending order of t).
    if (t1 > t2) {
        return {Intersection{t2, copy}, Intersection{t1, copy}};
    }
    return {Intersection{t1, copy}, Intersection{t2, copy}};
}