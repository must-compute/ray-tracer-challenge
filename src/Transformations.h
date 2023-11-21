#ifndef RAY_TRACER_CHALLENGE_TRANSFORMATIONS_H
#define RAY_TRACER_CHALLENGE_TRANSFORMATIONS_H

#include "Matrix.h"

namespace tf {
    Matrix<4, 4> translation(double x, double y, double z);
    Matrix<4, 4> scaling(double x, double y, double z);
    Matrix<4, 4> rotation_x(double x);
    Matrix<4, 4> rotation_y(double y);
    Matrix<4, 4> rotation_z(double z);
    Matrix<4, 4> shearing(double x, double y, double z);
}

#endif //RAY_TRACER_CHALLENGE_TRANSFORMATIONS_H
