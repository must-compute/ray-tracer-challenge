#ifndef RAY_TRACER_CHALLENGE_UTIL_H
#define RAY_TRACER_CHALLENGE_UTIL_H

#include <cmath>
#include <stdexcept>

class NotImplementedException : public std::logic_error {
public:
    NotImplementedException() : std::logic_error("Intentionally not implemented!!!") {}
};

constexpr double EPSILON = 1e-4;

[[nodiscard]] inline bool within_epsilon(double a, double b, double epsilon = EPSILON) {
    return std::abs(a - b) < epsilon;
}

#endif //RAY_TRACER_CHALLENGE_UTIL_H
