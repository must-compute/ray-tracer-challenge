#ifndef RAY_TRACER_CHALLENGE_INTERSECTIONCOMPUTATION_H
#define RAY_TRACER_CHALLENGE_INTERSECTIONCOMPUTATION_H

#include <memory>

#include "Tuple.h"

class Shape;

struct IntersectionComputation {
  double t{};
  const Shape *const object{};
  Point point{};
  Vector eyev{};
  Vector normalv{};
  bool inside{};

  // The point, slightly nudged in the direction of normalv so we guarantee we don't self-intersect due to
  // floating-point imprecision.
  Point over_point{};

  // The point, slightly nudged in the direction of -normalv, to be used by refracted rays.
  Point under_point{};
  Vector reflectv{};

  // Refractive indices (entering and exiting).
  double n1{};
  double n2{};

  [[nodiscard]] double schlick() const;
};

#endif //RAY_TRACER_CHALLENGE_INTERSECTIONCOMPUTATION_H
