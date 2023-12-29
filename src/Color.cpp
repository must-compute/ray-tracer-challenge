#include "Color.h"

// TODO should w always be either 1.0 or 0.0? Might wanna guarantee during construction
Color::Color(double r, double g, double b) : r_(r), g_(g), b_(b) {}

Color::Color() : r_(0.0), g_(0.0), b_(0.0) {}

bool Color::operator==(const Color &other) const {
  return within_epsilon(r_, other.r_)
      && within_epsilon(g_, other.g_)
      && within_epsilon(b_, other.b_);
}

Color Color::operator+(const Color &other) const {
  return {r_ + other.r_, g_ + other.g_, b_ + other.b_};
}

Color Color::operator-(const Color &other) const {
  return {r_ - other.r_, g_ - other.g_, b_ - other.b_};
}

Color Color::operator*(const double &scalar) const {
  return {r_ * scalar, g_ * scalar, b_ * scalar};
}

Color Color::operator/(const double &scalar) const {
  return {r_ / scalar, g_ / scalar, b_ / scalar};
}

double &Color::operator[](size_t i) {
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

double Color::red() const {
  return r_;
}

double Color::green() const {
  return g_;
}

double Color::blue() const {
  return b_;
}

std::array<double, 3> Color::rgb() const {
  return {r_, g_, b_};
}

Color Color::operator*(const Color &other) const {
  return {red() * other.red(), green() * other.green(), blue() * other.blue()};
}
