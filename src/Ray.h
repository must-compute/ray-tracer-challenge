#ifndef RAY_TRACER_CHALLENGE_RAY_H
#define RAY_TRACER_CHALLENGE_RAY_H

#include "Tuple.h"
#include "Sphere.h"

#include <vector>

class Ray {
public:
    Ray();

    Ray(const Tuple &origin_in, const Tuple &direction_in);

    // Returns the point if we move t units along the ray.
    Tuple position_at_t(double t) const;

    // TODO soon we'll have to replace these intersection doubles with actual Intersection objects.
    // Returns the points of intersection with the given shape. Intersection means the t value along the ray.
    std::vector<double> intersect(const Sphere &sphere) const;

private:
    // The origin of the ray. This should be a point (i.e. w == 1).
    Tuple origin;
    // The direction of the ray. This should be a vector (i.e. w == 0).
    Tuple direction;
};


#endif //RAY_TRACER_CHALLENGE_RAY_H
