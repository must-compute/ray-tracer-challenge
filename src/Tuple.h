#ifndef RAY_TRACER_CHALLENGE_TUPLE_H
#define RAY_TRACER_CHALLENGE_TUPLE_H

#include <tuple>
#include <array>
#include <cassert>
#include <ostream>

#include "util.h"

// TODO maybe split into Point and Vector classes (or use templating), so we limit invalid operations.
class Tuple {
private:
  double x_, y_, z_, w_;
public:

  Tuple(double x, double y, double z, double w);
  Tuple();

  [[nodiscard]] bool operator==(const Tuple &other) const;

  [[nodiscard]] Tuple operator+(const Tuple &other) const;

  [[nodiscard]] Tuple operator-(const Tuple &other) const;

  [[nodiscard]] Tuple operator*(const double &scalar) const;

  [[nodiscard]] Tuple operator/(const double &scalar) const;

  double &operator[](size_t i);

  [[nodiscard]] Tuple operator-() const;

  [[nodiscard]] double x() const;

  [[nodiscard]] double y() const;

  [[nodiscard]] double z() const;

  [[nodiscard]] double w() const;

  [[nodiscard]] bool is_point() const;

  [[nodiscard]] bool is_vector() const;

  [[nodiscard]] double magnitude() const;

  Tuple normalize() const;

  double dot(const Tuple &other) const;

  Tuple cross(const Tuple &other) const;

  // Return the current vector reflected about the given normal.
  Tuple reflect(const Tuple &normal) const;

  // For pretty printing in GTEST.
  friend std::ostream &operator<<(std::ostream &os, const Tuple &tup) {
    os << "Tuple: ";
    os << "{x: " << std::to_string(tup.x_) << ", y:" << std::to_string(tup.y_) << ", z:";
    os << std::to_string(tup.z_) << ", w:" << std::to_string(tup.w_) << "}";
    return os;
  }
};

Tuple make_point(double x, double y, double z);

Tuple make_vector(double x, double y, double z);

#endif //RAY_TRACER_CHALLENGE_TUPLE_H