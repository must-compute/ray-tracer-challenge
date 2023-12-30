#ifndef RAY_TRACER_CHALLENGE_TUPLE_H
#define RAY_TRACER_CHALLENGE_TUPLE_H

#include <tuple>
#include <array>
#include <cassert>
#include <ostream>

#include "util.h"

enum class TupleKind { Point, Vector };

template<TupleKind t>
class Tuple;

using Point = Tuple<TupleKind::Point>;
using Vector = Tuple<TupleKind::Vector>;

template<TupleKind t>
class Tuple {
private:
  double x_, y_, z_, w_;
  Tuple(double x, double y, double z, double w) : x_{x}, y_{y}, z_{z}, w_{w} {}

public:
  Tuple(double x, double y, double z) requires (t == TupleKind::Point): x_{x}, y_{y}, z_{z}, w_{1.0} {}
  Tuple(double x, double y, double z) requires (t == TupleKind::Vector): x_{x}, y_{y}, z_{z}, w_{0.0} {}

  Tuple() requires (t == TupleKind::Point): x_(0.0), y_(0.0), z_(0.0), w_(1.0) {}
  Tuple() requires (t == TupleKind::Vector): x_(0.0), y_(0.0), z_(0.0), w_(0.0) {}

  [[nodiscard]] bool operator==(const Tuple &other) const {
    return within_epsilon(x_, other.x_)
        && within_epsilon(y_, other.y_)
        && within_epsilon(z_, other.z_)
        && within_epsilon(w_, other.w_);
  }

  [[nodiscard]] Vector operator+(const Vector &other) const requires (t == TupleKind::Vector) {
    return {x_ + other.x(), y_ + other.y(), z_ + other.z(), w_ + other.w()};
  }

  [[nodiscard]] Point operator+(const Point &other) const requires (t == TupleKind::Vector) {
    return {x_ + other.x(), y_ + other.y(), z_ + other.z(), w_ + other.w()};
  }

  [[nodiscard]] Point operator+(const Vector &other) const requires (t == TupleKind::Point) {
    return {x_ + other.x(), y_ + other.y(), z_ + other.z(), w_ + other.w()};
  }

  [[nodiscard]] Vector operator-(const Point &other) const requires (t == TupleKind::Point) {
    return Vector{x_ - other.x(), y_ - other.y(), z_ - other.z()};
  }

  [[nodiscard]] Point operator-(const Vector &other) const requires (t == TupleKind::Point) {
    return Point{x_ - other.x(), y_ - other.y(), z_ - other.z()};
  }

  [[nodiscard]] Vector operator-(const Vector &other) const requires (t == TupleKind::Vector) {
    return {x_ - other.x(), y_ - other.y(), z_ - other.z(), w_ - other.w_};
  }

  [[nodiscard]] Vector operator*(const double &scalar) const requires (t == TupleKind::Vector) {
    return {x_ * scalar, y_ * scalar, z_ * scalar, w_ * scalar};
  }

  [[nodiscard]] Vector operator/(const double &scalar) const requires (t == TupleKind::Vector) {
    return {x_ / scalar, y_ / scalar, z_ / scalar, w_ / scalar};
  }

  double &operator[](size_t i) {
    switch (i) {
    case 0:return x_;
    case 1:return y_;
    case 2:return z_;
    case 3:return w_;
    default:assert(false);
    }
    // unreachable
    assert(false);
    return w_;
  }

  [[nodiscard]] Tuple operator-() const {
    return {-x_, -y_, -z_, -w_};
  }

  [[nodiscard]] double x() const {
    return x_;
  }

  [[nodiscard]] double y() const {
    return y_;
  }

  [[nodiscard]] double z() const {
    return z_;
  }

  // TODO turns out maybe we don't need w_ at all?
  [[nodiscard]] constexpr double w() const {
    if constexpr (t == TupleKind::Vector) {
      return 0.0;
    } else {
      return 1.0;
    }
  }

  [[nodiscard]] double magnitude() const requires (t == TupleKind::Vector) {
    return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);
  }

  Vector normalize() const requires (t == TupleKind::Vector) {
    const double mag = this->magnitude();
    return {x_ / mag, y_ / mag, z_ / mag, w_ / mag};
  }

  double dot(const Tuple &other) const requires (t == TupleKind::Vector) {
    return (x_ * other.x_) + (y_ * other.y_) + (z_ * other.z_) + (w_ * other.w_);
  }

  Vector cross(const Vector &other) const requires (t == TupleKind::Vector) {
    return {y_ * other.z_ - z_ * other.y_,
            z_ * other.x_ - x_ * other.z_,
            x_ * other.y_ - y_ * other.x_};
  }

  // Return the current vector reflected about the given normal.
  Vector reflect(const Vector &normal) const requires (t == TupleKind::Vector) {
    return *this - (normal * 2.0 * this->dot(normal));
  }

  // For pretty printing in GTEST.
  friend std::ostream &operator<<(std::ostream &os, const Tuple &tuple) {
    if constexpr (t == TupleKind::Point) {
      os << "Point: ";
    } else if constexpr (t == TupleKind::Vector) {
      os << "Vector: ";
    } else {
      os << "<<unimplemented pretty print of tuple kind>>";
    }

    os << "{x: " << std::to_string(tuple.x_) << ", y:" << std::to_string(tuple.y_) << ", z:";
    os << std::to_string(tuple.z_) << "}";
    return os;
  }

};

Point make_point(double x, double y, double z);

Vector make_vector(double x, double y, double z);

#endif //RAY_TRACER_CHALLENGE_TUPLE_H