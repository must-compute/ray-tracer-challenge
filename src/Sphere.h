#ifndef RAY_TRACER_CHALLENGE_SPHERE_H
#define RAY_TRACER_CHALLENGE_SPHERE_H


#include "Matrix.h"
#include "Transformations.h"

class Sphere {
public:
    Sphere() : transform_(tf::Transform::identity()) {}

    bool operator==(const Sphere &other) const = default;

    [[nodiscard]] tf::Transform transform() const;

    void set_transform(const tf::Transform &tf_in);

private:
    tf::Transform transform_;
};


#endif //RAY_TRACER_CHALLENGE_SPHERE_H
