#ifndef RAY_TRACER_CHALLENGE_CYLINDER_H
#define RAY_TRACER_CHALLENGE_CYLINDER_H

#include "Shape.h"
#include "Tuple.h"

class Ray;

class Cylinder final : public Shape {

public:
    bool operator==(const Cylinder &other) const = default;

    [[nodiscard]] Intersections local_intersect(const Ray &ray) override;

    [[nodiscard]] Tuple local_normal_at(const Tuple &point_in_object_space) const override;
};


#endif //RAY_TRACER_CHALLENGE_CYLINDER_H
