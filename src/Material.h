#ifndef RAY_TRACER_CHALLENGE_MATERIAL_H
#define RAY_TRACER_CHALLENGE_MATERIAL_H

#include <memory>

#include "Color.h"
#include "Tuple.h"
#include "PointLight.h"
#include "Pattern.h"

class Shape;

// TODO make into an aggregate (e.g. to allow using designated initializers)
struct Material {
    Material();

    bool operator==(const Material &other) const = default;

    Color color;
    double ambient{}; // non-negative, typically between 0 and 1
    double diffuse{}; // non-negative, typically between 0 and 1
    double specular{}; // non-negative, typically between 0 and 1
    double shininess{}; // non-negative, typically between 10 (large highlight) and 200 (small highlight)
    std::shared_ptr<Pattern> pattern{}; // if set, overrides "color" field.
    double reflective{}; // non-negative, typically between 0 and 1
    double transparency{}; // non-negative, typically between 0 and 1
    double refractive_index{};

    [[nodiscard]] Color lighting(
            const Shape &object,
            const PointLight &light,
            const Tuple &point,
            const Tuple &eyev,
            const Tuple &normalv,
            bool in_shadow) const;
};


#endif //RAY_TRACER_CHALLENGE_MATERIAL_H
