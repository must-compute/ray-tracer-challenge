#ifndef RAY_TRACER_CHALLENGE_PLANE_H
#define RAY_TRACER_CHALLENGE_PLANE_H

#include "Shape.h"

class Plane final : public Shape {
public:
    bool operator==(const Plane &other) const = default;

    [[nodiscard]] Intersections local_intersect(const Ray &ray) override;

    [[nodiscard]] Tuple local_normal_at(const Tuple &point_in_object_space) const override;
};


#endif //RAY_TRACER_CHALLENGE_PLANE_H
