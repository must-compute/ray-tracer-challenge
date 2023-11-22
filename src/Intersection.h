#ifndef RAY_TRACER_CHALLENGE_INTERSECTION_H
#define RAY_TRACER_CHALLENGE_INTERSECTION_H

#include "Sphere.h"
#include <vector>
#include <optional>

struct Intersection {
    bool operator==(const Intersection &other) const = default;

    double t;
    Sphere object;
};

using Intersections = std::vector<Intersection>;

std::optional<Intersection> hit(const Intersections& intersections);


#endif //RAY_TRACER_CHALLENGE_INTERSECTION_H
