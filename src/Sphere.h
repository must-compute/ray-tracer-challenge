#ifndef RAY_TRACER_CHALLENGE_SPHERE_H
#define RAY_TRACER_CHALLENGE_SPHERE_H


#include "Matrix.h"

class Sphere {
public:
    Sphere() : transform_(Matrix<4, 4>::identity()) {}

    bool operator==(const Sphere &other) const = default;

    [[nodiscard]] Matrix<4, 4> transform() const;

private:
    Matrix<4, 4> transform_;
};


#endif //RAY_TRACER_CHALLENGE_SPHERE_H
