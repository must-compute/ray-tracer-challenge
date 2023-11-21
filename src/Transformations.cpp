#include "Transformations.h"

namespace tf {
    Matrix<4, 4> translation(const double x, const double y, const double z) {
        return {
                std::array<std::array<double, 4>, 4>{
                        {{1.0, 0.0, 0.0, x},
                         {0.0, 1.0, 0.0, y},
                         {0.0, 0.0, 1.0, z},
                         {0.0, 0.0, 0.0, 1}}
                }
        };
    }

    Matrix<4, 4> scaling(const double x, const double y, const double z) {
        return {
                std::array<std::array<double, 4>, 4>{
                        {{x, 0.0, 0.0, 0},
                         {0.0, y, 0.0, 0},
                         {0.0, 0.0, z, 0},
                         {0.0, 0.0, 0.0, 1}}
                }
        };
    }

    Matrix<4, 4> rotation_x(const double x) {
        Matrix<4, 4> result{};
        // TODO implement
        return result;
    }

    Matrix<4, 4> rotation_y(const double y) {
        Matrix<4, 4> result{};
        // TODO implement
        return result;
    }

    Matrix<4, 4> rotation_z(const double z) {
        Matrix<4, 4> result{};
        // TODO implement
        return result;
    }

    Matrix<4, 4> shearing(const double x, const double y, const double z) {
        Matrix<4, 4> result{};
        // TODO implement
        return result;
    }
}
