#ifndef RAY_TRACER_CHALLENGE_SPHERE_H
#define RAY_TRACER_CHALLENGE_SPHERE_H


#include "Matrix.h"
#include "Material.h"
#include "Transformations.h"
#include "Tuple.h"

// TODO convert to struct & make the methods free functions
class Sphere {
public:
    Sphere() : transform_(tf::Transform::identity()) {}

    bool operator==(const Sphere &other) const = default;

    [[nodiscard]] tf::Transform transform() const;

    [[nodiscard]] Material material() const;

    void set_transform(const tf::Transform &tf_in);

    void set_material(const Material &m);

    [[nodiscard]] Tuple normal_at(const Tuple &point_in_world_space) const;


private:
    tf::Transform transform_;
    Material material_;
};


#endif //RAY_TRACER_CHALLENGE_SPHERE_H
