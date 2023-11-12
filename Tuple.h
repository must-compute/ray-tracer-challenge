#ifndef RAY_TRACER_CHALLENGE_TUPLE_H
#define RAY_TRACER_CHALLENGE_TUPLE_H

#include "util.h"

// TODO consider placing runtime checks against illegal w values (especially points).
// negation, magnitude, normalize, dot and cross-product.
struct Tuple {
    double x, y, z, w;

    Tuple(double x, double y, double z, double w);

    [[nodiscard]] bool is_point() const;

    [[nodiscard]] bool is_vector() const;

    bool operator==(const Tuple &other) const;

    Tuple operator+(const Tuple &other) const;

    Tuple operator-(const Tuple &other) const;

    Tuple operator-() const;

    Tuple operator*(const double &scalar) const;

    Tuple operator/(const double &scalar) const;

    [[nodiscard]] double magnitude() const;

    [[nodiscard]] Tuple normalize() const;

    [[nodiscard]] double dot(const Tuple &other) const;

    [[nodiscard]] Tuple cross(const Tuple &other) const;
};

// TODO this prevents implicit conversion for params. Not sure if it's idiomatic.
template<typename T>
Tuple make_point(T x, T y, T z) = delete;

Tuple make_point(double x, double y, double z);

Tuple make_vector(double x, double y, double z);

#endif //RAY_TRACER_CHALLENGE_TUPLE_H