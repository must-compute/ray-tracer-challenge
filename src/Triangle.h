#ifndef RAY_TRACER_CHALLENGE_TRIANGLE_H
#define RAY_TRACER_CHALLENGE_TRIANGLE_H

#include <optional>

#include "Shape.h"
#include "Tuple.h"

class Triangle : public Shape {
public:
  Triangle(const Point &p1, const Point &p2, const Point &p3);

  bool operator==(const Triangle &other) const = default;

  [[nodiscard]] Intersections local_intersect(const Ray &ray) override;

  [[nodiscard]] Vector local_normal_at(const Point &point_in_object_space,
                                       const std::optional<Intersection> &intersection) const override;

  [[nodiscard]] BoundingBox make_bounding_box() const override;

  [[nodiscard]] Point p1() const;

  [[nodiscard]] Point p2() const;

  [[nodiscard]] Point p3() const;

  [[nodiscard]] Vector e1() const;

  [[nodiscard]] Vector e2() const;

  [[nodiscard]] Vector normal() const;

protected:
  Point p1_{};
  Point p2_{};
  Point p3_{};
  Vector e1_{};
  Vector e2_{};
  Vector normal_{};
};

#endif //RAY_TRACER_CHALLENGE_TRIANGLE_H
