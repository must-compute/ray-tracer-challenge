#include "SmoothTriangle.h"

SmoothTriangle::SmoothTriangle(const Tuple &p1, const Tuple &p2, const Tuple &p3, const Tuple &n1, const Tuple &n2,
                               const Tuple &n3) : Triangle{p1, p2, p3}, n1_{n1}, n2_{n2}, n3_{n3} {}

Tuple SmoothTriangle::local_normal_at(const Tuple &point_in_object_space,
                                      const std::optional<Intersection> &intersection) const {
  assert(intersection);
  assert(intersection->u);
  assert(intersection->v);
  // Interpolate the normal using u and v to make the triangle face look smoother.
  return (n2_ * intersection->u.value()) +
      (n3_ * intersection->v.value()) +
      (n1_ * (1 - intersection->u.value() - intersection->v.value()));
}

Tuple SmoothTriangle::n1() const {
  return n1_;
}

Tuple SmoothTriangle::n2() const {
  return n2_;
}

Tuple SmoothTriangle::n3() const {
  return n3_;
}