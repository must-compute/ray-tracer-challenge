#include "Triangle.h"

Triangle::Triangle(const Tuple &p1, const Tuple &p2, const Tuple &p3) : p1_{p1}, p2_{p2}, p3_{p3}, e1_{p2_ - p1_},
                                                                        e2_{p3_ - p1_},
                                                                        normal_{e2_.cross(e1_).normalize()} {}

Intersections Triangle::local_intersect(const Ray &ray) {
    const auto triangle = std::make_shared<Triangle>(*this); // TODO this is silly. Will refactor in next commit.

    const auto determinant = ray.direction().cross(e2_).dot(e1_);
    if (within_epsilon(std::abs(determinant), 0)) {
        return {};
    }

    // TODO bogus intersection to avoid false-positive results. This function is still a work-in-progress
    return {Intersection{1.0, triangle}};
}

Tuple Triangle::local_normal_at(const Tuple &point_in_object_space) const {
    return normal_;
}

BoundingBox Triangle::make_bounding_box() const {
    return {};
}

Tuple Triangle::p1() const {
    return p1_;
}

Tuple Triangle::p2() const {
    return p2_;
}

Tuple Triangle::p3() const {
    return p3_;
}

Tuple Triangle::e1() const {
    return e1_;
}

Tuple Triangle::e2() const {
    return e2_;
}

Tuple Triangle::normal() const {
    return normal_;
}
