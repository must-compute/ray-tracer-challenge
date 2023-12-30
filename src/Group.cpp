#include "Group.h"
#include "util.h"

std::vector<std::shared_ptr<Shape>> Group::children() const {
  return children_;
}

void Group::add_child(const std::shared_ptr<Shape> &child) {
  children_.push_back(child);
  child->set_parent(shared_from_this());
}

Intersections Group::local_intersect(const Ray &ray) {
  if (!make_bounding_box().intersects(ray)) {
    return {};
  }

  Intersections xs{};
  for (const auto &shape : children_) {
    const auto shape_xs = shape->intersect(ray);
    xs.insert(xs.end(), shape_xs.begin(), shape_xs.end());
  }
  std::sort(xs.begin(), xs.end(), [](const auto &left, const auto &right) { return left.t < right.t; });
  return xs;
}

Vector Group::local_normal_at(const Point &point_in_object_space,
                              const std::optional<Intersection> &intersection) const {
  // Intentionally throw so we detect if we call this function (not supposed to).
  throw NotImplementedException{};
}

std::shared_ptr<Group> Group::make_group() {
  return std::make_shared<Group>(Group{});
}

BoundingBox Group::make_bounding_box() const {
  BoundingBox box{};
  for (const auto &child : children()) {
    box.add_box(child->make_bounding_box_in_parent_space());
  }
  return box;
}
