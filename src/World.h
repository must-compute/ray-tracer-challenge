#ifndef RAY_TRACER_CHALLENGE_WORLD_H
#define RAY_TRACER_CHALLENGE_WORLD_H

#include <vector>
#include <optional>
#include "Sphere.h"

struct World {
    // TODO should contain not just spheres
    std::vector<Sphere> objects{};
    std::optional<PointLight> light{};
};

[[nodiscard]] World make_default_world();


#endif //RAY_TRACER_CHALLENGE_WORLD_H