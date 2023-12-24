#ifndef RAY_TRACER_CHALLENGE_SPHERE_H
#define RAY_TRACER_CHALLENGE_SPHERE_H


#include "Shape.h"
#include "Matrix.h"
#include "Material.h"
#include "Transformations.h"
#include "Tuple.h"

class Ray;

class BoundingBox;

class Sphere final : public Shape {
public:
    bool operator==(const Sphere &other) const = default;

    [[nodiscard]] Intersections local_intersect(const Ray &ray) override;

    [[nodiscard]] Tuple local_normal_at(const Tuple &point_in_object_space) const override;

    [[nodiscard]] BoundingBox make_bounding_box() const override;
};


[[nodiscard]] Sphere make_glass_sphere();

#endif //RAY_TRACER_CHALLENGE_SPHERE_H
