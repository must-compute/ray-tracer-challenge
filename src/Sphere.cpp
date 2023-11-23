
#include "Sphere.h"

tf::Transform Sphere::transform() const {
    return transform_;
}

Material Sphere::material() const {
    return material_;
}

void Sphere::set_transform(const tf::Transform &tf_in) {
    transform_ = tf_in;
}

void Sphere::set_material(const Material &m) {
    material_ = m;
}

Tuple Sphere::normal_at(const Tuple &point_in_world_space) const {
    const auto point_in_object_space = transform_.inverse() * point_in_world_space;
    const auto normal_in_object_space = point_in_object_space - make_point(0.0, 0.0, 0.0);
    auto normal_in_world_space = transform_.inverse().transpose() * normal_in_object_space;
    // NOTE: we reset w to 0 in case the above operations give a non-zero w. Vectors should always have their w set to 0.
    normal_in_world_space = make_vector(normal_in_world_space.x(), normal_in_world_space.y(),
                                        normal_in_world_space.z());
    return normal_in_world_space.normalize();

}
