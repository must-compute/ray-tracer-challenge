#ifndef RAY_TRACER_CHALLENGE_INTERSECTION_H
#define RAY_TRACER_CHALLENGE_INTERSECTION_H

#include "IntersectionComputation.h"
#include <optional>
#include <vector>
#include <memory>

class Ray; // to avoid a circular dependency (Ray.h includes Intersection.h)
class Shape;


struct Intersection;

using Intersections = std::vector<Intersection>;

struct Intersection {
    bool operator==(const Intersection &other) const = default;

    bool operator<(const Intersection &other) const {
        return t < other.t;
    }

    [[nodiscard]] IntersectionComputation
    prepare_computations(const Ray &ray, const Intersections &xs = {}) const;

    double t{};
    std::shared_ptr<Shape> object{};
};

std::optional<Intersection> hit(const Intersections &intersections);


#endif //RAY_TRACER_CHALLENGE_INTERSECTION_H