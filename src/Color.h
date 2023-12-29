#ifndef RAY_TRACER_CHALLENGE_COLOR_H
#define RAY_TRACER_CHALLENGE_COLOR_H

#include <array>
#include <cassert>
#include <ostream>

#include "util.h"

class Color {
private:
  double r_, g_, b_;
public:

  // TODO should w always be either 1.0 or 0.0? Might wanna guarantee during construction
  Color(double r, double g, double b) : r_(r), g_(g), b_(b) {};

  Color() : r_(0.0), g_(0.0), b_(0.0) {};

  bool operator==(const Color &other) const {
    return within_epsilon(r_, other.r_)
        && within_epsilon(g_, other.g_)
        && within_epsilon(b_, other.b_);
  }

  Color operator+(const Color &other) const {
    return {r_ + other.r_, g_ + other.g_, b_ + other.b_};
  }

  Color operator-(const Color &other) const {
    return {r_ - other.r_, g_ - other.g_, b_ - other.b_};
  }

  Color operator*(const double &scalar) const {
    return {r_ * scalar, g_ * scalar, b_ * scalar};
  }

  Color operator/(const double &scalar) const {
    return {r_ / scalar, g_ / scalar, b_ / scalar};
  }

  double &operator[](size_t i) {
    switch (i) {
    case 0:return r_;
    case 1:return g_;
    case 2:return b_;
    default:assert(false);
    }
    // unreachable
    assert(false);
    return b_;
  }

  [[nodiscard]] double red() const {
    return r_;
  }

  [[nodiscard]] double green() const {
    return g_;
  }

  [[nodiscard]] double blue() const {
    return b_;
  }

  [[nodiscard]] std::array<double, 3> rgb() const {
    return {r_, g_, b_};
  }

  [[nodiscard]] Color operator*(const Color &other) const {
    return {red() * other.red(), green() * other.green(), blue() * other.blue()};
  }

  // For pretty printing in GTEST.
  friend std::ostream &operator<<(std::ostream &os, const Color &color) {
    os << "Color: ";
    os << "{red: " << std::to_string(color.r_) << ", green:" << std::to_string(color.g_) << ", blue:";
    os << std::to_string(color.b_) << "}";
    return os;
  }
};
#endif //RAY_TRACER_CHALLENGE_COLOR_H
