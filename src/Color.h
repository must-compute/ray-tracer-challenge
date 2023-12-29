#ifndef RAY_TRACER_CHALLENGE_COLOR_H
#define RAY_TRACER_CHALLENGE_COLOR_H

#include <array>
#include <cassert>
#include <ostream>

#include "util.h"

class Color {
private:
  double r_{}, g_{}, b_{};
public:
  Color(double r, double g, double b);
  Color();

  [[nodiscard]] bool operator==(const Color &other) const;

  [[nodiscard]] Color operator+(const Color &other) const;

  [[nodiscard]] Color operator-(const Color &other) const;

  [[nodiscard]] Color operator*(const double &scalar) const;

  [[nodiscard]] Color operator/(const double &scalar) const;

  double &operator[](size_t i);

  [[nodiscard]] double red() const;

  [[nodiscard]] double green() const;

  [[nodiscard]] double blue() const;

  [[nodiscard]] std::array<double, 3> rgb() const;

  [[nodiscard]] Color operator*(const Color &other) const;

  // For pretty printing in GTEST.
  friend std::ostream &operator<<(std::ostream &os, const Color &color) {
    os << "Color: ";
    os << "{red: " << std::to_string(color.r_) << ", green:" << std::to_string(color.g_) << ", blue:";
    os << std::to_string(color.b_) << "}";
    return os;
  }
};
#endif //RAY_TRACER_CHALLENGE_COLOR_H
