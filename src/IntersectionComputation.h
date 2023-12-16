#ifndef RAY_TRACER_CHALLENGE_INTERSECTIONCOMPUTATION_H
#define RAY_TRACER_CHALLENGE_INTERSECTIONCOMPUTATION_H

#include <memory>

#include "Tuple.h"

class Shape;

struct IntersectionComputation {

    double t{};
    std::shared_ptr<Shape> object{};
    Tuple point{};
    Tuple eyev{};
    Tuple normalv{};
    bool inside{};
    Tuple over_point{}; // The point, slightly nudged in the direction of normalv so we guarantee we don't self-intersect due to floating-point imprecision.
    Tuple under_point{}; // The point, slightly nudged in the direction of -normalv, to be used by refracted rays.
    Tuple reflectv{};
    // Refractive indices (entering and exiting).
    double n1{};
    double n2{};

    [[nodiscard]] double schlick() const;
};


#endif //RAY_TRACER_CHALLENGE_INTERSECTIONCOMPUTATION_H
