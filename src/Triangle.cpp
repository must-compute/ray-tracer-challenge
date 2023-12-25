#include "Triangle.h"

Triangle::Triangle(const Tuple &p1, const Tuple &p2, const Tuple &p3) : p1_{p1}, p2_{p2}, p3_{p3}, e1_{p2_ - p1_},
                                                                        e2_{p3_ - p1_},
                                                                        normal_{e2_.cross(e1_).normalize()} {}

Intersections Triangle::local_intersect(const Ray &ray) {
    const auto direction_cross_e2 = ray.direction().cross(e2_);
    const auto determinant = direction_cross_e2.dot(e1_);
    if (within_epsilon(std::abs(determinant), 0)) {
        return {};
    }

    const auto f = 1.0 / determinant;

    const auto p1_to_origin = ray.origin() - p1_;

    const auto u = f * p1_to_origin.dot(direction_cross_e2);

    if (u < 0.0 || u > 1.0) { // TODO should this range be inclusive or exclusive?
        return {};
    }

    const auto origin_cross_e1 = p1_to_origin.cross(e1_);
    const auto v = f * ray.direction().dot(origin_cross_e1);

    if (v < 0.0 || (u + v) > 1.0) {
        return {};
    }

    const auto t = f * e2_.dot(origin_cross_e1);
    return {Intersection{t, this}};
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
