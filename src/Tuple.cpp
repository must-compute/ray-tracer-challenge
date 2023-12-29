#include "Tuple.h"

// TODO should w always be either 1.0 or 0.0? Might wanna guarantee during construction
Tuple::Tuple(double x, double y, double z, double w) : x_(x), y_(y), z_(z), w_(w) {}

Tuple::Tuple() : x_(0.0), y_(0.0), z_(0.0), w_(0.0) {}

bool Tuple::operator==(const Tuple &other) const {
  return within_epsilon(x_, other.x_)
      && within_epsilon(y_, other.y_)
      && within_epsilon(z_, other.z_)
      && within_epsilon(w_, other.w_);
}

Tuple Tuple::operator+(const Tuple &other) const {
  return {x_ + other.x_, y_ + other.y_, z_ + other.z_, w_ + other.w_};
}

Tuple Tuple::operator-(const Tuple &other) const {
  return {x_ - other.x_, y_ - other.y_, z_ - other.z_, w_ - other.w_};
}

Tuple Tuple::operator*(const double &scalar) const {
  return {x_ * scalar, y_ * scalar, z_ * scalar, w_ * scalar};
}

Tuple Tuple::operator/(const double &scalar) const {
  return {x_ / scalar, y_ / scalar, z_ / scalar, w_ / scalar};
}

double &Tuple::operator[](size_t i) {
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

Tuple Tuple::operator-() const {
  return {-x_, -y_, -z_, -w_};
}

double Tuple::x() const {
  return x_;
}

double Tuple::y() const {
  return y_;
}

double Tuple::z() const {
  return z_;
}

double Tuple::w() const {
  return w_;
}

bool Tuple::is_point() const { return w_ == 1.0; }

bool Tuple::is_vector() const { return w_ == 0.0; }

double Tuple::magnitude() const {
  return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);
}

Tuple Tuple::normalize() const {
  const double mag = this->magnitude();
  return {x_ / mag, y_ / mag, z_ / mag, w_ / mag};
}

double Tuple::dot(const Tuple &other) const {
  return (x_ * other.x_) + (y_ * other.y_) + (z_ * other.z_) + (w_ * other.w_);
}

Tuple Tuple::cross(const Tuple &other) const {
  // TODO throw if Point
  return {y_ * other.z_ - z_ * other.y_,
          z_ * other.x_ - x_ * other.z_,
          x_ * other.y_ - y_ * other.x_,
          0.0};
}

// Return the current vector reflected about the given normal.
Tuple Tuple::reflect(const Tuple &normal) const {
  return *this - (normal * 2.0 * this->dot(normal));
}

Tuple make_point(double x, double y, double z) {
  return {x, y, z, 1.0};
}

Tuple make_vector(double x, double y, double z) {
  return {x, y, z, 0.0};
}
