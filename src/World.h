#ifndef RAY_TRACER_CHALLENGE_WORLD_H
#define RAY_TRACER_CHALLENGE_WORLD_H

#include <vector>
#include <optional>
#include <memory>

#include "Intersection.h"
#include "Shape.h"
#include "Ray.h"

struct World {
    std::vector<std::shared_ptr<Shape>> objects{};
    // TODO check page 96 for how to add multiple lights.
    std::optional<PointLight> light{};

    [[nodiscard]] Intersections intersect(const Ray &ray) const;

    [[nodiscard]] Color shade_hit(const IntersectionComputation &comps, size_t remaining = 5) const;

    [[nodiscard]] Color color_at(const Ray &ray, size_t remaining = 5) const;

    [[nodiscard]] bool is_shadowed(const Tuple &point) const;

    [[nodiscard]] Color reflected_color(const IntersectionComputation &comps, size_t remaining = 5) const;

    [[nodiscard]] Color refracted_color(const IntersectionComputation &comps, size_t remaining = 5) const;
};

[[nodiscard]] World make_default_world();


#endif //RAY_TRACER_CHALLENGE_WORLD_H
