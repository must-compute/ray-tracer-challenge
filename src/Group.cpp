#include "Group.h"
#include "util.h"

std::vector<std::shared_ptr<Shape>> Group::children() const {
    return children_;
}

// TODO: stare at this for a bit. A const-ref to a shared_ptr doesn't prevent us from mutating the pointed-at Shape. This seems wrong.
void Group::add_child(const std::shared_ptr<Shape> &child) {
    children_.push_back(child);
    // TODO: I'm not sure it makes sense (or that it's safe) to create a shared ptr to "this" in here. Walk through what happens when a tree of these is allocated and deallocated
    child->set_parent(std::make_shared<Group>(*this));
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
