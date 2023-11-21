#ifndef RAY_TRACER_CHALLENGE_TRANSFORMATIONS_H
#define RAY_TRACER_CHALLENGE_TRANSFORMATIONS_H

#include "Matrix.h"

namespace tf {
    Matrix<4, 4> translation(double x, double y, double z);
    Matrix<4, 4> scaling(double x, double y, double z);
    Matrix<4, 4> rotation_x(double theta);
    Matrix<4, 4> rotation_y(double theta);
    Matrix<4, 4> rotation_z(double theta);
    // NOTE: the parameter name x_y is the shearing factor for "x in proportion to y", and so on for the rest of them.
    Matrix<4, 4> shearing(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y);
}

#endif //RAY_TRACER_CHALLENGE_TRANSFORMATIONS_H
