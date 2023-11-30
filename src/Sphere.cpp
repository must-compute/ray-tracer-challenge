
#include "Sphere.h"
#include "Tuple.h"
#include "Ray.h"

#include <memory>

Tuple Sphere::local_normal_at(const Tuple &point_in_object_space) const {
    const auto normal_in_object_space = make_vector(
            point_in_object_space.x(),
            point_in_object_space.y(),
            point_in_object_space.z());

    return normal_in_object_space;
}


[[nodiscard]] Intersections Sphere::local_intersect(const Ray &ray) {
    const auto sphere_to_ray = ray.origin() - make_point(0.0, 0.0, 0.0);

    const auto a = ray.direction().dot(ray.direction());
    const auto b = 2 * ray.direction().dot(sphere_to_ray);
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

[[nodiscard]] Sphere make_glass_sphere() {
    auto sphere = Sphere{};
    auto material = Material{};
    material.transparency = 1.0;
    material.refractive_index = 1.5;
    sphere.set_material(material);
    return sphere;
}
