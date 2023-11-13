#ifndef RAY_TRACER_CHALLENGE_BASETUPLE_H
#define RAY_TRACER_CHALLENGE_BASETUPLE_H

#include "util.h"

enum class TupleOrColor {
    TUPLE,
    COLOR,
};

// TODO consider placing runtime checks against illegal w values (especially points).
// negation, magnitude, normalize, dot and cross-product.
template<TupleOrColor t>
class BaseTuple {
private:
    double x_, y_, z_, w_;
public:

    // TODO should w always be either 1.0 or 0.0? Might wanna guarantee during construction
    // Common methods
    BaseTuple(double x, double y, double z, double w) : x_(x), y_(y), z_(z), w_(w) {};

    bool operator==(const BaseTuple &other) const {
        return within_epsilon(x_, other.x_)
               && within_epsilon(y_, other.y_)
               && within_epsilon(z_, other.z_)
               && within_epsilon(w_, other.w_);
    }

    BaseTuple operator+(const BaseTuple &other) const {
        return {x_ + other.x_, y_ + other.y_, z_ + other.z_, w_ + other.w_};
    }

    BaseTuple operator-(const BaseTuple &other) const {
        return {x_ - other.x_, y_ - other.y_, z_ - other.z_, w_ - other.w_};
    }


    BaseTuple operator*(const double &scalar) const {
        return {x_ * scalar, y_ * scalar, z_ * scalar, w_ * scalar};
    }

    BaseTuple operator/(const double &scalar) const {
        return {x_ / scalar, y_ / scalar, z_ / scalar, w_ / scalar};
    }

    // Tuple-specific methods
    BaseTuple operator-() const requires (t == TupleOrColor::TUPLE) {
        return {-x_, -y_, -z_, -w_};
    }

    [[nodiscard]] double x() const requires (t == TupleOrColor::TUPLE) {
        return x_;
    }

    [[nodiscard]] double y() const requires (t == TupleOrColor::TUPLE) {
        return y_;
    }

    [[nodiscard]] double z() const requires (t == TupleOrColor::TUPLE) {
        return z_;
    }

    [[nodiscard]] double w() const requires (t == TupleOrColor::TUPLE) {
        return w_;
    }

    [[nodiscard]] bool is_point() const requires (t == TupleOrColor::TUPLE) { return w_ == 1.0; }

    [[nodiscard]] bool is_vector() const requires (t == TupleOrColor::TUPLE) { return w_ == 0.0; }

    [[nodiscard]] double magnitude() const requires (t == TupleOrColor::TUPLE) {
        return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);
    }

    BaseTuple normalize() const requires (t == TupleOrColor::TUPLE) {
        const double mag = this->magnitude();
        return {x_ / mag, y_ / mag, z_ / mag, w_ / mag};
    }

    double dot(const BaseTuple &other) const requires (t == TupleOrColor::TUPLE) {
        return (x_ * other.x_) + (y_ * other.y_) + (z_ * other.z_) + (w_ * other.w_);
    }

    BaseTuple cross(const BaseTuple &other) const requires (t == TupleOrColor::TUPLE) {
        // TODO throw if Point
        return {y_ * other.z_ - z_ * other.y_,
                z_ * other.x_ - x_ * other.z_,
                x_ * other.y_ - y_ * other.x_,
                0.0};
    }

    // Color-specific methods
    [[nodiscard]] double red() const requires (t == TupleOrColor::COLOR) {
        return x_;
    }

    [[nodiscard]] double green() const requires (t == TupleOrColor::COLOR) {
        return y_;
    }

    [[nodiscard]] double blue() const requires (t == TupleOrColor::COLOR) {
        return z_;
    }
};

#endif //RAY_TRACER_CHALLENGE_BASETUPLE_H
