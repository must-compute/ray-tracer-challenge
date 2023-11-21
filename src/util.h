#ifndef RAY_TRACER_CHALLENGE_UTIL_H
#define RAY_TRACER_CHALLENGE_UTIL_H

#include <cmath>

constexpr double EPSILON = 1e-14;

[[nodiscard]] inline bool within_epsilon(double a, double b, double epsilon = EPSILON) {
    return std::abs(a - b) < epsilon;
}

#endif //RAY_TRACER_CHALLENGE_UTIL_H
