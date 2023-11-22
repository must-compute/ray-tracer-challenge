#ifndef RAY_TRACER_CHALLENGE_SPHERE_H
#define RAY_TRACER_CHALLENGE_SPHERE_H


#include "Matrix.h"
#include "Transformations.h"
#include "Tuple.h"

class Sphere {
public:
    Sphere() : transform_(tf::Transform::identity()) {}

    bool operator==(const Sphere &other) const = default;

    [[nodiscard]] tf::Transform transform() const;

    void set_transform(const tf::Transform &tf_in);

    [[nodiscard]] Tuple normal_at(const Tuple &point_in_world_space) const;


private:
    tf::Transform transform_;
};


#endif //RAY_TRACER_CHALLENGE_SPHERE_H
