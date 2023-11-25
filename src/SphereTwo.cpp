#include "SphereTwo.h"


/*
Intersections SphereTwo::local_intersect(const Ray &ray) const {
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

    // NOTE: we care about the order of intersections (in ascending order of t).
    if (t1 > t2) {
        return {Intersection{t2, sphere}, Intersection{t1, sphere}};
    }
    return {Intersection{t1, sphere}, Intersection{t2, sphere}};
}


Tuple SphereTwo::normal_at(const Tuple &point_in_world_space) const {
    const auto point_in_object_space = transform_.inverse() * point_in_world_space;
    const auto normal_in_object_space = point_in_object_space - make_point(0.0, 0.0, 0.0);
    auto normal_in_world_space = transform_.inverse().transpose() * normal_in_object_space;
    // NOTE: we reset w to 0 in case the above operations give a non-zero w. Vectors should always have their w set to 0.
    normal_in_world_space = make_vector(normal_in_world_space.x(), normal_in_world_space.y(),
                                        normal_in_world_space.z());
    return normal_in_world_space.normalize();

}

 */