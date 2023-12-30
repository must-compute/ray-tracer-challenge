#ifndef RAY_TRACER_CHALLENGE_GROUP_H
#define RAY_TRACER_CHALLENGE_GROUP_H

#include <memory>
#include <optional>
#include <vector>

#include "Shape.h"

class BoundingBox;

class Group final : public Shape, public std::enable_shared_from_this<Group> {
private:
  Group() = default;

public:
  static std::shared_ptr<Group> make_group();

  bool operator==(const Group &other) const = delete;

  [[nodiscard]] std::vector<std::shared_ptr<Shape>> children() const;

  void add_child(const std::shared_ptr<Shape> &child); // TODO dont use const & here

  [[nodiscard]] Intersections local_intersect(const Ray &ray) override;

  [[nodiscard]] Vector local_normal_at(const Point &point_in_object_space,
                                       const std::optional<Intersection> &intersection) const override;

  [[nodiscard]] BoundingBox make_bounding_box() const override;

private:
  std::vector<std::shared_ptr<Shape>> children_;
};

#endif //RAY_TRACER_CHALLENGE_GROUP_H
