#include "BoundingBox.h"

BoundingBox::BoundingBox() :
        minimum_(make_point(std::numeric_limits<double>::infinity(),
                            std::numeric_limits<double>::infinity(),
                            std::numeric_limits<double>::infinity())),
        maximum_(make_point(-std::numeric_limits<double>::infinity(),
                            -std::numeric_limits<double>::infinity(),
                            -std::numeric_limits<double>::infinity())) {
}

BoundingBox::BoundingBox(const Tuple &minimum, const Tuple &maximum) : minimum_(minimum), maximum_(maximum) {
}

void BoundingBox::set_transform(const tf::Transform &transform) {
    const auto p1 = minimum_;
    const auto p2 = make_point(minimum_.x(), minimum_.y(), maximum_.z());
    const auto p3 = make_point(minimum_.x(), maximum_.y(), minimum_.z());
    const auto p4 = make_point(minimum_.x(), maximum_.y(), maximum_.z());
    const auto p5 = make_point(maximum_.x(), minimum_.y(), minimum_.z());
    const auto p6 = make_point(maximum_.x(), minimum_.y(), maximum_.z());
    const auto p7 = make_point(maximum_.x(), maximum_.y(), minimum_.z());
    const auto p8 = maximum_;

    for (const auto &point: {p1, p2, p3, p4, p5, p6, p7, p8}) {
        add_point(transform * point);
    }
}

Tuple BoundingBox::minimum() const {
    return minimum_;
}

Tuple BoundingBox::maximum() const {
    return maximum_;
}

void BoundingBox::add_point(const Tuple &point) {
    // Adjust the bounding box to contain the given point.
    minimum_ = make_point(
            std::min(point.x(), minimum_.x()),
            std::min(point.y(), minimum_.y()),
            std::min(point.z(), minimum_.z()));
    maximum_ = make_point(
            std::max(point.x(), maximum_.x()),
            std::max(point.y(), maximum_.y()),
            std::max(point.z(), maximum_.z()));
}

void BoundingBox::add_box(const BoundingBox &other) {
    // Combine two boxes and return the union.
    add_point(other.minimum());
    add_point(other.maximum());
}

bool BoundingBox::contains_point(const Tuple &point) const {
    return minimum_.x() <= point.x() && point.x() <= maximum_.x() &&
           minimum_.y() <= point.y() && point.y() <= maximum_.y() &&
           minimum_.z() <= point.z() && point.z() <= maximum_.z();
}

bool BoundingBox::contains_box(const BoundingBox &other) const {
    return minimum_.x() <= other.minimum().x() &&
           minimum_.y() <= other.minimum().y() &&
           minimum_.z() <= other.minimum().z() &&
           maximum_.x() >= other.maximum().x() &&
           maximum_.y() >= other.maximum().y() &&
           maximum_.z() >= other.maximum().z();
}

