#ifndef RAY_TRACER_CHALLENGE_COLOR_H
#define RAY_TRACER_CHALLENGE_COLOR_H

#include <tuple>
#include <array>
#include <cassert>
#include <ostream>

#include "util.h"

class Color {
private:
  double x_, y_, z_, w_;
public:

  // TODO should w always be either 1.0 or 0.0? Might wanna guarantee during construction
  Color(double x, double y, double z, double w) : x_(x), y_(y), z_(z), w_(w) {};

  Color() : x_(0.0), y_(0.0), z_(0.0), w_(0.0) {};

  bool operator==(const Color &other) const {
    return within_epsilon(x_, other.x_)
        && within_epsilon(y_, other.y_)
        && within_epsilon(z_, other.z_)
        && within_epsilon(w_, other.w_);
  }

  Color operator+(const Color &other) const {
    return {x_ + other.x_, y_ + other.y_, z_ + other.z_, w_ + other.w_};
  }

  Color operator-(const Color &other) const {
    return {x_ - other.x_, y_ - other.y_, z_ - other.z_, w_ - other.w_};
  }

  Color operator*(const double &scalar) const {
    return {x_ * scalar, y_ * scalar, z_ * scalar, w_ * scalar};
  }

  Color operator/(const double &scalar) const {
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

  [[nodiscard]] double red() const {
    return x_;
  }

  [[nodiscard]] double green() const {
    return y_;
  }

  [[nodiscard]] double blue() const {
    return z_;
  }

  [[nodiscard]] std::array<double, 3> rgb() const {
    return {x_, y_, z_};
  }

  [[nodiscard]] Color operator*(const Color &other) const {
    // TODO assuming alpha is not needed
    return {red() * other.red(), green() * other.green(), blue() * other.blue(), 0.0};
  }

  // For pretty printing in GTEST.
  friend std::ostream &operator<<(std::ostream &os, const Color &tup) {
    os << "Color<" << "COLOR>\n";
    os << "{red: " << std::to_string(tup.x_) << ", green:" << std::to_string(tup.y_) << ", blue:";
    os << std::to_string(tup.z_) << "}";
    return os;
  }
};
[[nodiscard]] Color make_color(double red, double green, double blue);

#endif //RAY_TRACER_CHALLENGE_COLOR_H
