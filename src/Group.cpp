#include "Group.h"
#include "util.h"

std::vector<std::shared_ptr<Shape>> Group::children() const {
    return children_;
}

void Group::add_child(const std::shared_ptr<Group> &group, const std::shared_ptr<Shape> &child) {
    group->children_.push_back(child);
    child->set_parent(group);
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