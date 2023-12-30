#ifndef RAY_TRACER_CHALLENGE_SMOOTHTRIANGLE_H
#define RAY_TRACER_CHALLENGE_SMOOTHTRIANGLE_H

#include "Tuple.h"
#include "Triangle.h"

class SmoothTriangle final : public Triangle {
public:
  SmoothTriangle(const Point &p1, const Point &p2, const Point &p3, const Vector &n1, const Vector &n2,
                 const Vector &n3);

  bool operator==(const SmoothTriangle &other) const = default;

  [[nodiscard]] Vector
  local_normal_at(const Point &point_in_object_space,
                  const std::optional<Intersection> &intersection) const override;

  [[nodiscard]] Vector n1() const;

  [[nodiscard]] Vector n2() const;

  [[nodiscard]] Vector n3() const;

private:
  Vector n1_{};
  Vector n2_{};
  Vector n3_{};
};

#endif //RAY_TRACER_CHALLENGE_SMOOTHTRIANGLE_H
