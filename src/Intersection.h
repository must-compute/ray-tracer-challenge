#ifndef RAY_TRACER_CHALLENGE_INTERSECTION_H
#define RAY_TRACER_CHALLENGE_INTERSECTION_H

#include "Sphere.h"
#include "IntersectionComputation.h"
#include <optional>
#include <vector>

class Ray; // to avoid a circular dependency (Ray.h includes Intersection.h)

struct Intersection {
    bool operator==(const Intersection &other) const = default;

    bool operator<(const Intersection &other) const {
        return t < other.t;
    }

    [[nodiscard]] IntersectionComputation prepare_computations(const Ray &ray) const;

    double t{};
    Sphere object;
};

using Intersections = std::vector<Intersection>;

std::optional<Intersection> hit(const Intersections &intersections);


#endif //RAY_TRACER_CHALLENGE_INTERSECTION_H