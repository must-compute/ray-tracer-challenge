#ifndef RAY_TRACER_CHALLENGE_TRANSFORMATIONS_H
#define RAY_TRACER_CHALLENGE_TRANSFORMATIONS_H

#include "Matrix.h"

namespace tf {
    Matrix<4, 4> translation(const double x, const double y, const double z);
    Matrix<4, 4> scaling(const double x, const double y, const double z);
    Matrix<4, 4> rotation_x(const double x);
    Matrix<4, 4> rotation_y(const double y);
    Matrix<4, 4> rotation_z(const double z);
    Matrix<4, 4> shearing(const double x, const double y, const double z);
}

#endif //RAY_TRACER_CHALLENGE_TRANSFORMATIONS_H
