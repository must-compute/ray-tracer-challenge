#include "Sphere.h"
#include "Tuple.h"
#include "Ray.h"

#include <memory>

Vector Sphere::local_normal_at(const Point &point_in_object_space,
                               const std::optional<Intersection> &intersection) const {
  const auto normal_in_object_space = Vector(
      point_in_object_space.x(),
      point_in_object_space.y(),
      point_in_object_space.z());

  return normal_in_object_space;
}

[[nodiscard]] Intersections Sphere::local_intersect(const Ray &ray) {
  const auto sphere_to_ray = ray.origin() - Point{0.0, 0.0, 0.0};

  const auto a = ray.direction().dot(ray.direction());
  const auto b = 2 * ray.direction().dot(sphere_to_ray);
  const auto c = sphere_to_ray.dot(sphere_to_ray) - 1.0;

  const auto discriminant = (b * b) - 4 * (a * c);

  if (discriminant < 0.0) {
    // MISS!
    return {};
  }

  const auto discr_sqrt = std::sqrt(discriminant);
  const auto t1 = (-b - discr_sqrt) / (2 * a);
  const auto t2 = (-b + discr_sqrt) / (2 * a);

  // NOTE: we care about the order of intersections (in ascending order of t).
  if (t1 > t2) {
    return {Intersection{t2, this}, Intersection{t1, this}};
  }
  return {Intersection{t1, this}, Intersection{t2, this}};
}

BoundingBox Sphere::make_bounding_box() const {
  return BoundingBox{Point{-1.0, -1.0, -1.0}, Point{1.0, 1.0, 1.0}};
}

[[nodiscard]] Sphere make_glass_sphere() {
  auto sphere = Sphere{};
  auto material = Material{};
  material.transparency = 1.0;
  material.refractive_index = 1.5;
  sphere.set_material(material);
  return sphere;
}
