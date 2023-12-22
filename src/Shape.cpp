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

[[nodiscard]] std::shared_ptr<Shape> Shape::parent() const {
    return parent_;
}

void Shape::set_transform(const tf::Transform& tf_in) {
    transform_ = tf_in;
}

void Shape::set_material(const Material& m) {
    material_ = m;
}

void Shape::set_parent(const std::shared_ptr<Shape>& parent) {
    parent_ = parent;
}

Intersections Shape::intersect(const Ray& ray) {
    const auto local_ray = ray.transform(transform_.inverse());
    return local_intersect(local_ray);
}

Tuple Shape::normal_at(const Tuple& point_in_world_space) const {
    const auto point_in_object_space = world_to_object(point_in_world_space);
    const auto normal_in_object_space = local_normal_at(point_in_object_space);
    return normal_to_world(normal_in_object_space);
}

Tuple Shape::world_to_object(const Tuple& point_in_world_space) const {
    // Recurse using the parent.
    if (parent_ != nullptr) {
        return transform_.inverse() * parent_->world_to_object(point_in_world_space);
    }

    // Recursion base case.
    return transform_.inverse() * point_in_world_space;
}

Tuple Shape::normal_to_world(const Tuple& normal_in_object_space) const {
    auto normal = transform_.inverse().transpose() * normal_in_object_space;
    // NOTE: we reset w to 0 in case the above operations give a non-zero w. Vectors should always have their w set to 0.
    normal = make_vector(normal.x(), normal.y(), normal.z());
    normal = normal.normalize();

    if (parent_ != nullptr) {
        normal = parent_->normal_to_world(normal);
    }
    return normal;
}
