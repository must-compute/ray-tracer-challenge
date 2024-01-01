#include "TestShape.h"

Vector
TestShape::local_normal_at(const Point &point_in_object_space, const std::optional<Intersection> &intersection) const {
  return Vector{point_in_object_space.x(), point_in_object_space.y(), point_in_object_space.z()};
}

Intersections TestShape::local_intersect(const Ray &ray) {
  local_ray_ = ray;
  return {};
}

std::optional<Ray> TestShape::local_ray() const {
  return local_ray_;
}

BoundingBox TestShape::make_bounding_box() const {
  return BoundingBox{Point{-1.0, -1.0, -1.0}, Point{1.0, 1.0, 1.0}};
}
