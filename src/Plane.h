#ifndef RAY_TRACER_CHALLENGE_PLANE_H
#define RAY_TRACER_CHALLENGE_PLANE_H

#include <optional>

#include "Shape.h"

class BoundingBox;

class Plane final : public Shape {
public:
  bool operator==(const Plane &other) const = default;

  [[nodiscard]] Intersections local_intersect(const Ray &ray) override;

  [[nodiscard]] Vector local_normal_at(const Point &point_in_object_space,
                                       const std::optional<Intersection> &intersection) const override;

  [[nodiscard]] BoundingBox make_bounding_box() const override;
};

#endif //RAY_TRACER_CHALLENGE_PLANE_H
