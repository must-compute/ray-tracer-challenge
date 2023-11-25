#ifndef RAY_TRACER_CHALLENGE_TESTSHAPE_H
#define RAY_TRACER_CHALLENGE_TESTSHAPE_H

#include "Shape.h"
#include "Intersection.h"
#include "Ray.h"
#include "Material.h"
#include "Transformations.h"
#include "Tuple.h"

class TestShape final : public Shape {
public:

    [[nodiscard]] Ray local_ray() const;

private:
    [[nodiscard]] Intersections local_intersect(const Ray &ray) override;

    [[nodiscard]] Tuple local_normal_at(const Tuple &point_in_world_space) const override;

    Ray local_ray_;
};


#endif //RAY_TRACER_CHALLENGE_TESTSHAPE_H
