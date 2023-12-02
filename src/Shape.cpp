#include "Shape.h"

tf::Transform Shape::transform() const {
    return transform_;
}

Material Shape::material() const {
    return material_;
}

bool Shape::casts_shadow() const {
    return material_.casts_shadow;
}

void Shape::set_transform(const tf::Transform &tf_in) {
    transform_ = tf_in;
}

void Shape::set_material(const Material &m) {
    material_ = m;
}

Intersections Shape::intersect(const Ray &ray) {
    const auto local_ray = ray.transform(transform_.inverse());
    return local_intersect(local_ray);
}

Tuple Shape::normal_at(const Tuple &point_in_world_space) const {
    const auto point_in_object_space = transform_.inverse() * point_in_world_space;
    const auto normal_in_object_space = local_normal_at(point_in_object_space);
    auto normal_in_world_space = transform_.inverse().transpose() * normal_in_object_space;
    // NOTE: we reset w to 0 in case the above operations give a non-zero w. Vectors should always have their w set to 0.
    normal_in_world_space = make_vector(normal_in_world_space.x(), normal_in_world_space.y(),
                                        normal_in_world_space.z());
    return normal_in_world_space.normalize();
}
