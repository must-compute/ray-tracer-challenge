#ifndef RAY_TRACER_CHALLENGE_CONE_H
#define RAY_TRACER_CHALLENGE_CONE_H

#include <limits>
#include <optional>

#include "Shape.h"

class BoundingBox;

// A double-napped cone
class Cone final : public Shape {
public:
  [[nodiscard]] double minimum() const;

  [[nodiscard]] double maximum() const;

  [[nodiscard]] bool closed() const;

  void set_minimum(double min);

  void set_maximum(double max);

  void set_closed(bool closed);

  [[nodiscard]] Intersections local_intersect(const Ray &ray) override;

  [[nodiscard]] Vector local_normal_at(const Point &point_in_object_space,
                                       const std::optional<Intersection> &intersection) const override;

  [[nodiscard]] BoundingBox make_bounding_box() const override;

  Intersections intersect_caps(const Ray &ray) const;

private:
  double minimum_ = -std::numeric_limits<double>::infinity();
  double maximum_ = std::numeric_limits<double>::infinity();
  bool closed_ = false;
};

#endif //RAY_TRACER_CHALLENGE_CONE_H
