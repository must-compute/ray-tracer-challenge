#ifndef RAY_TRACER_CHALLENGE_INTERSECTIONCOMPUTATION_H
#define RAY_TRACER_CHALLENGE_INTERSECTIONCOMPUTATION_H

#include "Sphere.h"
#include "Tuple.h"

struct IntersectionComputation {

    double t{};
    Sphere object{};
    Tuple point{};
    Tuple eyev{};
    Tuple normalv{};
    bool inside{};

};


#endif //RAY_TRACER_CHALLENGE_INTERSECTIONCOMPUTATION_H
