#ifndef RAY_TRACER_CHALLENGE_SPHERETWO_H
#define RAY_TRACER_CHALLENGE_SPHERETWO_H

#include "Matrix.h"
#include "Material.h"
#include "Transformations.h"
#include "Tuple.h"
#include "Intersection.h"
#include "Shape.h"
#include "Ray.h"

// TODO convert to struct & make the methods free functions
class SphereTwo : public Shape {
public:
    //SphereTwo() : Shape() {}

    //bool operator==(const SphereTwo &other) const = default;

    [[nodiscard]] Intersections local_intersect(const Ray &ray) override;

    [[nodiscard]] tf::Transform transform() const;

    [[nodiscard]] Material material() const;

    void set_transform(const tf::Transform &tf_in);

    void set_material(const Material &m);

    [[nodiscard]] Tuple normal_at(const Tuple &point_in_world_space) const;

};

#endif //RAY_TRACER_CHALLENGE_SPHERETWO_H
