#ifndef RAY_TRACER_CHALLENGE_TESTSHAPE_H
#define RAY_TRACER_CHALLENGE_TESTSHAPE_H

#include <optional>

#include "Shape.h"
#include "Intersection.h"
#include "Ray.h"
#include "Tuple.h"

class TestShape final : public Shape {
public:

  [[nodiscard]] std::optional<Ray> local_ray() const;

  [[nodiscard]] BoundingBox make_bounding_box() const override;

private:
  [[nodiscard]] Intersections local_intersect(const Ray &ray) override;

  [[nodiscard]] Tuple local_normal_at(const Tuple &point_in_object_space,
                                      const std::optional<Intersection> &intersection) const override;

  std::optional<Ray> local_ray_;
};

#endif //RAY_TRACER_CHALLENGE_TESTSHAPE_H
