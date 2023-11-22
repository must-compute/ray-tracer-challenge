#ifndef RAY_TRACER_CHALLENGE_RAY_H
#define RAY_TRACER_CHALLENGE_RAY_H

#include "Intersection.h"
#include "Matrix.h"
#include "Sphere.h"
#include "Tuple.h"

#include <vector>

class Ray {
public:
    Ray();

    Ray(const Tuple &origin_in, const Tuple &direction_in);

    [[nodiscard]] Tuple origin() const;

    [[nodiscard]] Tuple direction() const;

    // Returns the point if we move t units along the ray.
    [[nodiscard]] Tuple position_at_t(double t) const;

    // Returns the points of intersection with the given shape.
    [[nodiscard]] Intersections intersect(const Sphere &sphere) const;

    [[nodiscard]] Ray transform(const Matrix<4, 4> &m) const;

private:
    // The origin of the ray. This should be a point (i.e. w == 1).
    Tuple origin_;
    // The direction of the ray. This should be a vector (i.e. w == 0).
    Tuple direction_;
};


#endif //RAY_TRACER_CHALLENGE_RAY_H
