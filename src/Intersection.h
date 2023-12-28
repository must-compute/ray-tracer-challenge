#ifndef RAY_TRACER_CHALLENGE_INTERSECTION_H
#define RAY_TRACER_CHALLENGE_INTERSECTION_H

#include "IntersectionComputation.h"
#include <optional>
#include <vector>
#include <memory>

class Ray; // to avoid a circular dependency (Ray.h includes Intersection.h)
class Shape;

struct Intersection;

using Intersections = std::vector<Intersection>;

struct Intersection {
  Intersection(const double t_in, const Shape *const object_in, const std::optional<double> &u_in = std::nullopt,
               const std::optional<double> &v_in = std::nullopt) : t{t_in}, object{object_in}, u{u_in}, v{v_in} {}

  bool operator==(const Intersection &other) const = default;

  bool operator<(const Intersection &other) const {
    return t < other.t;
  }

  [[nodiscard]] IntersectionComputation
  prepare_computations(const Ray &ray, const Intersections &xs = {}) const;

  double t{};
  const Shape *object
      {}; // TODO in a perfect world, we'd want the pointer itself to be const, but that deletes the copy assignment, which makes using the Intersection a pain (see prepare_computations).
  std::optional<double> u{};
  std::optional<double> v{};
};

std::optional<Intersection> hit(const Intersections &intersections);

#endif //RAY_TRACER_CHALLENGE_INTERSECTION_H