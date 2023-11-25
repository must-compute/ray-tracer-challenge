#include "TestShape.h"

Tuple TestShape::local_normal_at(const Tuple &point_in_world_space) const {
    return make_vector(point_in_world_space.x(), point_in_world_space.y(), point_in_world_space.z());
}

Intersections TestShape::local_intersect(const Ray &ray) {
    local_ray_ = ray;
    return {};
}

Ray TestShape::local_ray() const {
    return local_ray_;
}