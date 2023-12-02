#include "IntersectionComputation.h"

double IntersectionComputation::schlick() const {
    auto cos = eyev.dot(normalv);

    if (n1 > n2) {
        const auto n = n1 / n2;
        const auto sin2_t = std::pow(n, 2) * (1.0 - std::pow(cos, 2));
        if (sin2_t > 1.0) {
            return 1.0;
        }

        const auto cos_t = std::sqrt(1.0 - sin2_t);

        // when n1 > n2, use cos(theta_t) instead
        cos = cos_t;
    }

    const auto r0 = std::pow((n1 - n2) / (n1 + n2), 2);
    return r0 + (1.0 - r0) * std::pow(1.0 - cos, 5);
}
