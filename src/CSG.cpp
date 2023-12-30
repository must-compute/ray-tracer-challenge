#include "CSG.h"
#include "Intersection.h"
#include "Ray.h"
#include "Group.h"
#include "util.h"

bool contains(Shape *const container_shape, const Shape *const target) {
  // if group, recurse through children
  if (const auto ptr = dynamic_cast<Group *>(container_shape)) {
    return std::any_of(ptr->children().begin(),
                       ptr->children().end(),
                       [target](const std::shared_ptr<Shape> &child) { return contains(child.get(), target); });
  }

  // if csg, recurse through left and right
  if (const auto ptr = dynamic_cast<CSG *>(container_shape)) {
    return contains(ptr->left().get(), target) || contains(ptr->right().get(), target);
  }

  // if any other type (base case, or leaf nodes in the tree), just check directly for equality with target.
  return container_shape == target;
}

std::shared_ptr<CSG> CSG::make_csg(CSGOperation operation,
                                   std::shared_ptr<Shape> left,
                                   std::shared_ptr<Shape> right) {
  auto csg = std::make_shared<CSG>(CSG{operation, std::move(left), std::move(right)});
  // Set the parents of your children to be yourself.
  assert(csg->left_);
  assert(csg->right_);
  csg->left_->set_parent(csg->shared_from_this());
  csg->right_->set_parent(csg->shared_from_this());
  return csg;
}

bool CSG::intersection_allowed(CSGOperation op, bool left_hit, bool inside_left, bool inside_right) {
  if (op == CSGOperation::Union) {
    return (left_hit and not inside_right) or (not left_hit and not inside_left);
  } else if (op == CSGOperation::Intersection) {
    return (left_hit and inside_right) or (not left_hit and inside_left);
  } else if (op == CSGOperation::Difference) {
    return (left_hit and not inside_right) or (not left_hit and inside_left);
  }

  assert(false); // invalid op, or unreachable
  return {};
}

Intersections CSG::filter_intersections(const Intersections &intersections) const {
  // Begin outside of both children
  bool in_left{false};
  bool in_right{false};

  Intersections result{};

  for (const auto &i : intersections) {
    // If i.object is part of the left child, then left_hit is true, otherwise it's false.
    const bool left_hit = contains(left_.get(), i.object);

    if (intersection_allowed(operation_, left_hit, in_left, in_right)) {
      result.push_back(i);
    }

    // Depending on which object was hit, toggle either in_left or in_right
    if (left_hit) {
      in_left = !in_left;
    } else {
      in_right = !in_right;
    }
  }

  return result;
}

CSGOperation CSG::operation() const {
  return operation_;
}

std::shared_ptr<Shape> CSG::left() const {
  return left_;
}

std::shared_ptr<Shape> CSG::right() const {
  return right_;
}

Intersections CSG::local_intersect(const Ray &ray) {
  if (!make_bounding_box().intersects(ray)) {
    return {};
  }

  auto left_xs = left_->intersect(ray);
  const auto right_xs = right_->intersect(ray);

  auto &xs = left_xs;
  xs.insert(xs.end(), right_xs.begin(), right_xs.end());
  std::sort(xs.begin(), xs.end(), [](const Intersection &left, const Intersection &right) { return left.t < right.t; });

  return filter_intersections(xs);
}

Vector CSG::local_normal_at(const Point &point_in_object_space, const std::optional<Intersection> &intersection) const {
  // Intentionally throw so we detect if we call this function (not supposed to).
  throw NotImplementedException{};
}

BoundingBox CSG::make_bounding_box() const {
  BoundingBox box{};
  for (const auto &child : {left_, right_}) {
    box.add_box(child->make_bounding_box_in_parent_space());
  }
  return box;
}
