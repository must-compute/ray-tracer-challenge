#ifndef RAY_TRACER_CHALLENGE_TRANSFORMATIONS_H
#define RAY_TRACER_CHALLENGE_TRANSFORMATIONS_H

#include "Matrix.h"
#include "Tuple.h"

namespace tf {
    using Transform = Matrix<4, 4>;

    Transform translation(double x, double y, double z);

    Transform scaling(double x, double y, double z);

    Transform rotation_x(double theta);

    Transform rotation_y(double theta);

    Transform rotation_z(double theta);

    // NOTE: the parameter name x_y is the shearing factor for "x in proportion to y", and so on for the rest of them.
    Transform shearing(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y);

    [[nodiscard]] Transform view_transform(const Tuple &from, const Tuple &to, const Tuple &up);

}

#endif //RAY_TRACER_CHALLENGE_TRANSFORMATIONS_H
