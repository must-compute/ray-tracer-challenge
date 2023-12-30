#include "Triangle.h"

Triangle::Triangle(const Point &p1, const Point &p2, const Point &p3) : p1_{p1}, p2_{p2}, p3_{p3}, e1_{p2_ - p1_},
                                                                        e2_{p3_ - p1_},
                                                                        normal_{e2_.cross(e1_).normalize()} {}

Intersections Triangle::local_intersect(const Ray &ray) {
  const auto direction_cross_e2 = ray.direction().cross(e2_);
  const auto determinant = direction_cross_e2.dot(e1_);
  if (within_epsilon(std::abs(determinant), 0)) {
    return {};
  }

  const auto f = 1.0 / determinant;

  const auto p1_to_origin = ray.origin() - p1_;

  const auto u = f * p1_to_origin.dot(direction_cross_e2);

  if (u < 0.0 || u > 1.0) { // TODO should this range be inclusive or exclusive?
    return {};
  }

  const auto origin_cross_e1 = p1_to_origin.cross(e1_);
  const auto v = f * ray.direction().dot(origin_cross_e1);

  if (v < 0.0 || (u + v) > 1.0) {
    return {};
  }

  const auto t = f * e2_.dot(origin_cross_e1);
  return {Intersection{t, this, u, v}};
}

Vector Triangle::local_normal_at(const Point &point_in_object_space,
                                 const std::optional<Intersection> &intersection) const {
  return normal_;
}

BoundingBox Triangle::make_bounding_box() const {
  BoundingBox box{};
  box.add_point(p1_);
  box.add_point(p2_);
  box.add_point(p3_);
  return box;
}

Point Triangle::p1() const {
  return p1_;
}

Point Triangle::p2() const {
  return p2_;
}

Point Triangle::p3() const {
  return p3_;
}

Vector Triangle::e1() const {
  return e1_;
}

Vector Triangle::e2() const {
  return e2_;
}

Vector Triangle::normal() const {
  return normal_;
}
