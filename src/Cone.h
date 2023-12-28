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

  [[nodiscard]] Tuple local_normal_at(const Tuple &point_in_object_space,
                                      const std::optional<Intersection> &intersection) const override;

  [[nodiscard]] BoundingBox make_bounding_box() const override;

  // TODO might need to be updated to avoid mutating intersections
  void intersect_caps(const Ray &ray, Intersections &xs) const;

private:
  double minimum_ = -std::numeric_limits<double>::infinity();
  double maximum_ = std::numeric_limits<double>::infinity();
  bool closed_ = false;
};

#endif //RAY_TRACER_CHALLENGE_CONE_H
