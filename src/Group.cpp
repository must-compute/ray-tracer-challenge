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
    Intersections xs{};
    for (const auto &shape: children_) {
        const auto shape_xs = shape->intersect(ray);
        xs.insert(xs.end(), shape_xs.begin(), shape_xs.end());
    }
    std::sort(xs.begin(), xs.end(), [](const auto &left, const auto &right) { return left.t < right.t; });
    return xs;
}

Tuple Group::local_normal_at(const Tuple &point_in_object_space) const {
    // Intentionally throw so we detect if we call this function (not supposed to).
    throw NotImplementedException{};
}

std::shared_ptr<Group> Group::make_group() {
    return std::make_shared<Group>(Group{});
}

Bounds Group::make_bounds() const {
    // First, get the bounds of each child in the group.
    for (const auto &child: children()) {
        const auto b = child->make_bounds();
    }
    return {};
}
