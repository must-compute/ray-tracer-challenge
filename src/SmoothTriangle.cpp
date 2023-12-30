#include "SmoothTriangle.h"

SmoothTriangle::SmoothTriangle(const Point &p1, const Point &p2, const Point &p3, const Vector &n1, const Vector &n2,
                               const Vector &n3) : Triangle{p1, p2, p3}, n1_{n1}, n2_{n2}, n3_{n3} {}

Vector SmoothTriangle::local_normal_at(const Point &point_in_object_space,
                                       const std::optional<Intersection> &intersection) const {
  assert(intersection);
  assert(intersection->u);
  assert(intersection->v);
  // Interpolate the normal using u and v to make the triangle face look smoother.
  return (n2_ * intersection->u.value()) +
      (n3_ * intersection->v.value()) +
      (n1_ * (1 - intersection->u.value() - intersection->v.value()));
}

Vector SmoothTriangle::n1() const {
  return n1_;
}

Vector SmoothTriangle::n2() const {
  return n2_;
}

Vector SmoothTriangle::n3() const {
  return n3_;
}