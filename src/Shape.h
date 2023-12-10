#ifndef RAY_TRACER_CHALLENGE_SHAPE_H
#define RAY_TRACER_CHALLENGE_SHAPE_H

#include "Matrix.h"
#include "Material.h"
#include "Transformations.h"
#include "Tuple.h"
#include "Intersection.h"
#include "Ray.h"


class Shape {
public:
    Shape() : transform_(tf::Transform::identity()) {}

    virtual ~Shape() = default;

    Shape(const Shape &other) = default;

    bool operator==(const Shape &other) const = default;

    // NOTE: intersect() is non-const only because the TestShape test requires it to mutate an internal member.
    [[nodiscard]] Intersections intersect(const Ray &ray);

    [[nodiscard]] Tuple normal_at(const Tuple &point_in_world_space) const;

    [[nodiscard]] tf::Transform transform() const;

    [[nodiscard]] Material material() const;

    [[nodiscard]] bool casts_shadow() const;

    void set_transform(const tf::Transform &tf_in);

    void set_material(const Material &m);


protected:
    tf::Transform transform_;
    Material material_;

    [[nodiscard]] virtual Intersections local_intersect(const Ray &ray) = 0;

    [[nodiscard]] virtual Tuple local_normal_at(const Tuple &point_in_object_space) const = 0;

};


#endif //RAY_TRACER_CHALLENGE_SHAPE_H
