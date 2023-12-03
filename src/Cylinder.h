#ifndef RAY_TRACER_CHALLENGE_CYLINDER_H
#define RAY_TRACER_CHALLENGE_CYLINDER_H

#include <limits>

#include "Shape.h"
#include "Tuple.h"

class Ray;

class Cylinder final : public Shape {

public:
    bool operator==(const Cylinder &other) const = default;

    [[nodiscard]] double minimum() const;

    [[nodiscard]] double maximum() const;

    void set_minimum(double min);

    void set_maximum(double max);

    [[nodiscard]] Intersections local_intersect(const Ray &ray) override;

    [[nodiscard]] Tuple local_normal_at(const Tuple &point_in_object_space) const override;

private:
    double minimum_ = -std::numeric_limits<double>::infinity();
    double maximum_ = std::numeric_limits<double>::infinity();
};


#endif //RAY_TRACER_CHALLENGE_CYLINDER_H
