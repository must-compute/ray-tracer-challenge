#include "CSG.h"
#include "Intersection.h"
#include "Ray.h"
#include "util.h"

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
    // TODO
    throw NotImplementedException{};
}

Tuple CSG::local_normal_at(const Tuple &point_in_object_space, const std::optional<Intersection> &intersection) const {
    // TODO
    throw NotImplementedException{};
}

BoundingBox CSG::make_bounding_box() const {
    // TODO
    throw NotImplementedException{};
}
