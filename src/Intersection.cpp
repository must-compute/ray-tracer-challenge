
#include "Intersection.h"
#include "Ray.h"
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

IntersectionComputation Intersection::prepare_computations(const Ray &ray) const {
    auto comps = IntersectionComputation{};

    comps.t = t;
    comps.object = object;
    comps.point = ray.position_at_t(comps.t);
    comps.eyev = -ray.direction();
    comps.normalv = comps.object.normal_at(comps.point);

    if (comps.normalv.dot(comps.eyev) < 0) {
        comps.inside = true;
        comps.normalv = -comps.normalv;
    } else {
        comps.inside = false;
    }

    return comps;
}
