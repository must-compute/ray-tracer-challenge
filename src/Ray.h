#ifndef RAY_TRACER_CHALLENGE_RAY_H
#define RAY_TRACER_CHALLENGE_RAY_H

#include "Intersection.h"
#include "Matrix.h"
#include "Tuple.h"
#include "Transformations.h"

#include <vector>

class Ray {
public:
  Ray();

  Ray(const Point &origin_in, const Vector &direction_in);

  [[nodiscard]] Point origin() const;

  [[nodiscard]] Vector direction() const;

  // Returns the point if we move t units along the ray.
  [[nodiscard]] Point position_at_t(double t) const;

  [[nodiscard]] Ray transform(const tf::Transform &m) const;

private:
  // The origin of the ray. This should be a point (i.e. w == 1).
  Point origin_;
  // The direction of the ray. This should be a vector (i.e. w == 0).
  Vector direction_;
};

#endif //RAY_TRACER_CHALLENGE_RAY_H
