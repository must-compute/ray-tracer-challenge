#ifndef RAY_TRACER_CHALLENGE_MATERIAL_H
#define RAY_TRACER_CHALLENGE_MATERIAL_H

#include "Color.h"

struct Material {
    Material();

    bool operator==(const Material &other) const = default;

    Color color;
    double ambient{}; // non-negative, typically between 0 and 1
    double diffuse{}; // non-negative, typically between 0 and 1
    double specular{}; // non-negative, typically between 0 and 1
    double shininess{}; // non-negative, typically between 10 (large highlight) and 200 (small highlight)
};


#endif //RAY_TRACER_CHALLENGE_MATERIAL_H