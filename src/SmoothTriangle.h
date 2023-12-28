#ifndef RAY_TRACER_CHALLENGE_SMOOTHTRIANGLE_H
#define RAY_TRACER_CHALLENGE_SMOOTHTRIANGLE_H

#include "Tuple.h"
#include "Triangle.h"

class SmoothTriangle final : public Triangle {
public:
  SmoothTriangle(const Tuple &p1, const Tuple &p2, const Tuple &p3, const Tuple &n1, const Tuple &n2,
                 const Tuple &n3);

  bool operator==(const SmoothTriangle &other) const = default;

  [[nodiscard]] Tuple
  local_normal_at(const Tuple &point_in_object_space,
                  const std::optional<Intersection> &intersection) const override;

  [[nodiscard]] Tuple n1() const;

  [[nodiscard]] Tuple n2() const;

  [[nodiscard]] Tuple n3() const;

private:
  Tuple n1_{};
  Tuple n2_{};
  Tuple n3_{};
};

#endif //RAY_TRACER_CHALLENGE_SMOOTHTRIANGLE_H
