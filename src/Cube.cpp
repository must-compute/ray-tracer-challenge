#include <limits>

#include "Cube.h"
#include "Tuple.h"
#include "Ray.h"
#include "util.h"

std::pair<double, double> Cube::check_axis(double origin, double direction) {
  const auto t_min_numerator = -1.0 - origin;
  const auto t_max_numerator = 1.0 - origin;

  double t_min{};
  double t_max{};
  if (std::abs(direction) >= EPSILON) {
    t_min = t_min_numerator / direction;
    t_max = t_max_numerator / direction;
  } else {
    t_min = t_min_numerator * std::numeric_limits<double>::infinity();
    t_max = t_max_numerator * std::numeric_limits<double>::infinity();
  }

  if (t_min > t_max) {
    std::swap(t_min, t_max);
  }

  return {t_min, t_max};
}

Vector Cube::local_normal_at(const Point &point_in_object_space,
                             const std::optional<Intersection> &intersection) const {
  const std::vector<double> maxs = {std::abs(point_in_object_space.x()),
                                    std::abs(point_in_object_space.y()),
                                    std::abs(point_in_object_space.z())};
  const auto max_c = *std::max_element(maxs.begin(), maxs.end());

  if (max_c == std::abs(point_in_object_space.x())) {
    return make_vector(point_in_object_space.x(), 0.0, 0.0);
  } else if (max_c == std::abs(point_in_object_space.y())) {
    return make_vector(0.0, point_in_object_space.y(), 0.0);
  } else if (max_c == std::abs(point_in_object_space.z())) {
    return make_vector(0.0, 0.0, point_in_object_space.z());
  }

  assert(false); // unreachable
  return {};
}

[[nodiscard]] Intersections Cube::local_intersect(const Ray &ray) {
  const auto [x_t_min, x_t_max] = check_axis(ray.origin().x(), ray.direction().x());
  const auto [y_t_min, y_t_max] = check_axis(ray.origin().y(), ray.direction().y());
  const auto [z_t_min, z_t_max] = check_axis(ray.origin().z(), ray.direction().z());

  const std::vector<double> mins{x_t_min, y_t_min, z_t_min};
  const std::vector<double> maxs{x_t_max, y_t_max, z_t_max};
  const auto t_min = *std::max_element(mins.begin(), mins.end());
  const auto t_max = *std::min_element(maxs.begin(), maxs.end());

  if (t_min > t_max) { // ray miss
    return {};
  }

  return {Intersection{t_min, this}, Intersection{t_max, this}};
}

BoundingBox Cube::make_bounding_box() const {
  return {make_point(-1.0, -1.0, -1.0), make_point(1.0, 1.0, 1.0)};
}
