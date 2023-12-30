#include "BoundingBox.h"

BoundingBox::BoundingBox() :
    minimum_(make_point(std::numeric_limits<double>::infinity(),
                        std::numeric_limits<double>::infinity(),
                        std::numeric_limits<double>::infinity())),
    maximum_(make_point(-std::numeric_limits<double>::infinity(),
                        -std::numeric_limits<double>::infinity(),
                        -std::numeric_limits<double>::infinity())) {
}

BoundingBox::BoundingBox(const Point &minimum, const Point &maximum) : minimum_(minimum), maximum_(maximum) {
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

  auto new_bounding_box = BoundingBox{};
  for (const auto &point : {p1, p2, p3, p4, p5, p6, p7, p8}) {
    new_bounding_box.add_point(transform * point);
  }
  minimum_ = new_bounding_box.minimum_;
  maximum_ = new_bounding_box.maximum_;
}

Point BoundingBox::minimum() const {
  return minimum_;
}

Point BoundingBox::maximum() const {
  return maximum_;
}

void BoundingBox::add_point(const Point &point) {
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

bool BoundingBox::contains_point(const Point &point) const {
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

bool BoundingBox::intersects(const Ray &ray) const {
  const auto [x_t_min, x_t_max] = check_axis(ray.origin().x(), ray.direction().x(), minimum_.x(), maximum_.x());
  const auto [y_t_min, y_t_max] = check_axis(ray.origin().y(), ray.direction().y(), minimum_.y(), maximum_.y());
  const auto [z_t_min, z_t_max] = check_axis(ray.origin().z(), ray.direction().z(), minimum_.z(), maximum_.z());

  const std::vector<double> mins{x_t_min, y_t_min, z_t_min};
  const std::vector<double> maxs{x_t_max, y_t_max, z_t_max};
  const auto t_min = *std::max_element(mins.begin(), mins.end());
  const auto t_max = *std::min_element(maxs.begin(), maxs.end());

  if (t_min > t_max) { // ray miss
    return false;
  }

  return true;
}

std::pair<double, double> BoundingBox::check_axis(double origin, double direction, double min, double max) {
  const auto t_min_numerator = min - origin;
  const auto t_max_numerator = max - origin;

  double t_min{};
  double t_max{};
  if (std::abs(direction) >= EPSILON) {
    t_min = t_min_numerator / direction;
    t_max = t_max_numerator / direction;
  } else {
    t_min = t_min_numerator * std::numeric_limits<double>::infinity();
    t_max = t_max_numerator * std::numeric_limits<double>::infinity();
  }

  if (t_min > t_max) {
    std::swap(t_min, t_max);
  }

  return {t_min, t_max};
}
