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

    [[nodiscard]] bool closed() const;

    void set_minimum(double min);

    void set_maximum(double max);

    void set_closed(bool closed);

    // TODO might need to be updated to avoid mutating intersections
    void intersect_caps(const Ray &ray, Intersections &xs) const;

    [[nodiscard]] Intersections local_intersect(const Ray &ray) override;

    [[nodiscard]] Tuple local_normal_at(const Tuple &point_in_object_space) const override;

private:
    double minimum_ = -std::numeric_limits<double>::infinity();
    double maximum_ = std::numeric_limits<double>::infinity();
    bool closed_ = false;
};


#endif //RAY_TRACER_CHALLENGE_CYLINDER_H
