#ifndef RAY_TRACER_CHALLENGE_INTERSECTIONCOMPUTATION_H
#define RAY_TRACER_CHALLENGE_INTERSECTIONCOMPUTATION_H

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
    Tuple reflectv{};

};


#endif //RAY_TRACER_CHALLENGE_INTERSECTIONCOMPUTATION_H
