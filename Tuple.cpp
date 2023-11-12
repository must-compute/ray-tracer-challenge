#include "Tuple.h"
#include "util.h"

// TODO should w always be either 1.0 or 0.0? Might wanna guarantee during construction
Tuple::Tuple(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {};

[[nodiscard]] bool Tuple::is_point() const { return w == 1.0; }

[[nodiscard]] bool Tuple::is_vector() const { return w == 0.0; }

bool Tuple::operator==(const Tuple &other) const {
    return within_epsilon(x, other.x)
           && within_epsilon(y, other.y)
           && within_epsilon(z, other.z)
           && within_epsilon(w, other.w);
}

Tuple Tuple::operator+(const Tuple &other) const {
    return {x + other.x, y + other.y, z + other.z, w + other.w};
}

Tuple Tuple::operator-(const Tuple &other) const {
    return {x - other.x, y - other.y, z - other.z, w - other.w};
}

Tuple Tuple::operator-() const {
    return {-x, -y, -z, -w};
}

Tuple Tuple::operator*(const double &scalar) const {
    return {x * scalar, y * scalar, z * scalar, w * scalar};
}

Tuple Tuple::operator/(const double &scalar) const {
    return {x / scalar, y / scalar, z / scalar, w / scalar};
}

double Tuple::magnitude() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

Tuple Tuple::normalize() const {
    const double mag = this->magnitude();
    return {x / mag, y / mag, z / mag, w / mag};
}

double Tuple::dot(const Tuple &other) const {
    return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
}

Tuple Tuple::cross(const Tuple &other) const {
    // TODO throw if Point
    return make_vector(y * other.z - z * other.y,
                       z * other.x - x * other.z,
                       x * other.y - y * other.x);
}

[[nodiscard]] Tuple make_point(double x, double y, double z) {
    return {x, y, z, 1.0};
}

[[nodiscard]] Tuple make_vector(double x, double y, double z) {
    return {x, y, z, 0.0};
}

