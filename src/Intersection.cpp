#include "Intersection.h"

#include <algorithm>
#include <optional>

#include "Ray.h"
#include "Shape.h"

std::optional<Intersection> hit(const Intersections &intersections) {
  if (intersections.empty()) {
    return std::nullopt;
  }

  std::optional<Intersections::const_iterator> min_intersection;
  for (auto iter = intersections.begin(); iter < intersections.end(); ++iter) {
    if (iter->t >= 0.0) {
      if (!min_intersection || iter->t < min_intersection.value()->t) {
        min_intersection = iter;
      }
    }
  }
  return min_intersection ? std::make_optional(*min_intersection.value()) : std::nullopt;
}

IntersectionComputation Intersection::prepare_computations(const Ray &ray, const Intersections &xs) const {
  assert(object);

  const auto eyev = -ray.direction();
  const auto point = ray.position_at_t(t);

  auto normalv = object->normal_at(point, *this);
  bool inside{false};
  if (normalv.dot(eyev) < 0) {
    inside = true;
    normalv = -normalv;
  } else {
    inside = false;
  }

  const auto reflectv = ray.direction().reflect(normalv);
  const auto over_point = point + (normalv * EPSILON);
  const auto under_point = point - (normalv * EPSILON);

  auto n1 = 0.0;
  auto n2 = 0.0;

  // Compute the refractive indices (n1 and n2).
  std::vector<const Shape *> seen_objects{};
  Intersections xs_to_check{xs};
  if (xs_to_check.empty()) {
    xs_to_check.push_back(*this);
  }
  for (const auto &i : xs_to_check) {
    // Set n1 if this intersection is the hit.
    if (i == *this) {
      if (seen_objects.empty()) {
        n1 = 1.0;
      } else {
        assert(seen_objects.back());
        n1 = seen_objects.back()->material().refractive_index;
      }
    }

    if (std::find(seen_objects.begin(), seen_objects.end(), i.object) != seen_objects.end()) {
      // If we've seen this object before, delete it (we're exiting it).
      seen_objects.erase(std::remove(seen_objects.begin(), seen_objects.end(), i.object), seen_objects.end());
    } else {
      // Otherwise, add this seen object (we're entering it).
      seen_objects.push_back(i.object);
    }

    // Set n2 and break if this intersection is a hit.
    if (i == *this) {
      if (seen_objects.empty()) {
        n2 = 1.0;
      } else {
        assert(seen_objects.back());
        n2 = seen_objects.back()->material().refractive_index;
      }

      break;
    }
  }

  return IntersectionComputation{
      .t = t,
      .object = object,
      .point = point,
      .eyev = eyev,
      .normalv = normalv,
      .inside = inside,
      .over_point = over_point,
      .under_point = under_point,
      .reflectv = reflectv,
      .n1 = n1,
      .n2 = n2
  };
}
