#ifndef RAY_TRACER_CHALLENGE_SHAPE_H
#define RAY_TRACER_CHALLENGE_SHAPE_H

#include <memory>
#include <optional>

#include "Matrix.h"
#include "Material.h"
#include "Transformations.h"
#include "Tuple.h"
#include "Intersection.h"
#include "BoundingBox.h"
#include "Ray.h"

class Shape {
public:
  Shape() : transform_(tf::Transform::identity()) {
  }

  virtual ~Shape() = default;

  Shape(const Shape &other) = default;

  bool operator==(const Shape &other) const = default;

  // NOTE: intersect() is non-const only because the TestShape test requires it to mutate an internal member.
  [[nodiscard]] Intersections intersect(const Ray &ray);

  [[nodiscard]] Vector normal_at(const Point &point_in_world_space,
                                 const std::optional<Intersection> &intersection = std::nullopt) const;

  [[nodiscard]] Point world_to_object(const Point &point_in_world_space) const;

  [[nodiscard]] Vector normal_to_world(const Vector &normal_in_object_space) const;

  [[nodiscard]] tf::Transform transform() const;

  [[nodiscard]] Material material() const;

  [[nodiscard]] bool casts_shadow() const;

  [[nodiscard]] std::shared_ptr<Shape> parent() const;

  void set_transform(const tf::Transform &tf_in);

  void set_material(const Material &m);

  void set_parent(const std::shared_ptr<Shape> &parent);

  [[nodiscard]] virtual BoundingBox make_bounding_box() const = 0;

  [[nodiscard]] BoundingBox make_bounding_box_in_parent_space() const;

protected:
  tf::Transform transform_;
  Material material_;
  std::shared_ptr<Shape> parent_;

  [[nodiscard]] virtual Intersections local_intersect(const Ray &ray) = 0;

  // NOTE: intersection is only used by SmoothTriangle derived class. All other classes use nullopt (can't use
  // default args for virtual functions because it's confusing).
  [[nodiscard]] virtual Vector local_normal_at(const Point &point_in_object_space,
                                               const std::optional<Intersection> &intersection) const = 0;
};

#endif //RAY_TRACER_CHALLENGE_SHAPE_H
