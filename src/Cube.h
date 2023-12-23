#ifndef RAY_TRACER_CHALLENGE_CUBE_H
#define RAY_TRACER_CHALLENGE_CUBE_H

#include "Shape.h"
#include "Tuple.h"

class Ray;

class Bounds;

class Cube final : public Shape {
public:
    bool operator==(const Cube &other) const = default;

    [[nodiscard]] static std::pair<double, double> check_axis(double origin, double direction);

    [[nodiscard]] Intersections local_intersect(const Ray &ray) override;

    [[nodiscard]] Tuple local_normal_at(const Tuple &point_in_object_space) const override;

    [[nodiscard]] Bounds make_bounds() const override;
};

#endif //RAY_TRACER_CHALLENGE_CUBE_H
