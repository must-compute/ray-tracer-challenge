
#include "Intersection.h"
#include <algorithm>

std::optional<Intersection> hit(const Intersections &intersections) {
    // Return the intersection with the smallest non-negative t. Negative ts don't count because they're behind the ray origin.
    Intersections nonnegative{};
    std::copy_if(intersections.begin(), intersections.end(), std::back_inserter(nonnegative),
                 [](const Intersection &i) { return i.t >= 0.0; });

    const auto iter = std::min_element(nonnegative.begin(), nonnegative.end(),
                                       [](const Intersection &a, const Intersection &b) { return a.t < b.t; });
    if (iter != nonnegative.end()) {
        return *iter;
    }
    return std::nullopt;
}
