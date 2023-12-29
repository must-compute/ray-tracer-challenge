#ifndef RAY_TRACER_CHALLENGE_TUPLE_H
#define RAY_TRACER_CHALLENGE_TUPLE_H

#include <tuple>
#include <array>
#include <cassert>
#include <ostream>

#include "util.h"

class Tuple {
private:
  double x_, y_, z_, w_;
public:

  // TODO should w always be either 1.0 or 0.0? Might wanna guarantee during construction
  Tuple(double x, double y, double z, double w) : x_(x), y_(y), z_(z), w_(w) {};

  Tuple() : x_(0.0), y_(0.0), z_(0.0), w_(0.0) {};

  bool operator==(const Tuple &other) const {
    return within_epsilon(x_, other.x_)
        && within_epsilon(y_, other.y_)
        && within_epsilon(z_, other.z_)
        && within_epsilon(w_, other.w_);
  }

  Tuple operator+(const Tuple &other) const {
    return {x_ + other.x_, y_ + other.y_, z_ + other.z_, w_ + other.w_};
  }

  Tuple operator-(const Tuple &other) const {
    return {x_ - other.x_, y_ - other.y_, z_ - other.z_, w_ - other.w_};
  }

  Tuple operator*(const double &scalar) const {
    return {x_ * scalar, y_ * scalar, z_ * scalar, w_ * scalar};
  }

  Tuple operator/(const double &scalar) const {
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

  Tuple operator-() const {
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

  [[nodiscard]] double w() const {
    return w_;
  }

  [[nodiscard]] bool is_point() const { return w_ == 1.0; }

  [[nodiscard]] bool is_vector() const { return w_ == 0.0; }

  [[nodiscard]] double magnitude() const {
    return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);
  }

  Tuple normalize() const {
    const double mag = this->magnitude();
    return {x_ / mag, y_ / mag, z_ / mag, w_ / mag};
  }

  double dot(const Tuple &other) const {
    return (x_ * other.x_) + (y_ * other.y_) + (z_ * other.z_) + (w_ * other.w_);
  }

  Tuple cross(const Tuple &other) const {
    // TODO throw if Point
    return {y_ * other.z_ - z_ * other.y_,
            z_ * other.x_ - x_ * other.z_,
            x_ * other.y_ - y_ * other.x_,
            0.0};
  }

  // Return the current vector reflected about the given normal.
  Tuple reflect(const Tuple &normal) const {
    return *this - (normal * 2.0 * this->dot(normal));
  }

  // For pretty printing in GTEST.
  friend std::ostream &operator<<(std::ostream &os, const Tuple &tup) {
    os << "Tuple: ";
    os << "{x: " << std::to_string(tup.x_) << ", y:" << std::to_string(tup.y_) << ", z:";
    os << std::to_string(tup.z_) << ", w:" << std::to_string(tup.w_) << "}";
    return os;
  }
};

// TODO this prevents implicit conversion for params. Not sure if it's idiomatic.
//template<typename T>
//Tuple make_point(T x, T y, T z) = delete;

Tuple make_point(double x, double y, double z);

Tuple make_vector(double x, double y, double z);

#endif //RAY_TRACER_CHALLENGE_TUPLE_H