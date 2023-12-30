#include "Ray.h"

Ray::Ray() : origin_(make_point(0.0, 0.0, 0.0)), direction_(make_vector(0.0, 0.0, 0.0)) {}

Ray::Ray(const Point &origin_in, const Vector &direction_in) : origin_(origin_in), direction_(direction_in) {
}

Point Ray::position_at_t(double t) const {
  return origin_ + direction_ * t;
}

Point Ray::origin() const {
  return origin_;
}

Vector Ray::direction() const {
  return direction_;
}

Ray Ray::transform(const tf::Transform &m) const {
  return {m * origin_, m * direction_};
}
