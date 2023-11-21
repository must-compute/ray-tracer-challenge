#include "Transformations.h"

#include <cmath>

namespace tf {
    Matrix<4, 4> translation(const double x, const double y, const double z) {
        return {
                std::array<std::array<double, 4>, 4>{
                        {{1.0, 0.0, 0.0, x},
                         {0.0, 1.0, 0.0, y},
                         {0.0, 0.0, 1.0, z},
                         {0.0, 0.0, 0.0, 1.0}}
                }
        };
    }

    Matrix<4, 4> scaling(const double x, const double y, const double z) {
        return {
                std::array<std::array<double, 4>, 4>{
                        {{x, 0.0, 0.0, 0},
                         {0.0, y, 0.0, 0},
                         {0.0, 0.0, z, 0},
                         {0.0, 0.0, 0.0, 1.0}}
                }
        };
    }

    Matrix<4, 4> rotation_x(const double theta) {
        using namespace std;
        return {
                std::array<std::array<double, 4>, 4>{
                        {{1.0, 0.0, 0.0, 0},
                         {0.0, cos(theta), -sin(theta), 0},
                         {0.0, sin(theta), cos(theta), 0},
                         {0.0, 0.0, 0.0, 1.0}}
                }
        };
    }

    Matrix<4, 4> rotation_y(const double theta) {
        using namespace std;
        return {
                std::array<std::array<double, 4>, 4>{
                        {{cos(theta), 0.0, sin(theta), 0},
                         {0.0, 1.0, 0.0, 0},
                         {-sin(theta), 0.0, cos(theta), 0},
                         {0.0, 0.0, 0.0, 1.0}}
                }
        };
    }

    Matrix<4, 4> rotation_z(const double theta) {
        using namespace std;
        return {
                std::array<std::array<double, 4>, 4>{
                        {{cos(theta), -sin(theta), 0.0, 0},
                         {sin(theta), cos(theta), 0.0, 0},
                         {0.0, 0.0, 1.0, 0},
                         {0.0, 0.0, 0.0, 1.0}}
                }
        };
    }

    Matrix<4, 4> shearing(const double x, const double y, const double z) {
        Matrix<4, 4> result{};
        // TODO implement
        return result;
    }
}
