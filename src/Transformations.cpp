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

// NOTE: the parameter name x_y is the shearing factor for "x in proportion to y", and so on for the rest of them.
Matrix<4, 4> shearing(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y) {
  return {
      std::array<std::array<double, 4>, 4>{
          {{1.0, x_y, x_z, 0.0},
           {y_x, 1.0, y_z, 0.0},
           {z_x, z_y, 1.0, 0.0},
           {0.0, 0.0, 0.0, 1.0}}
      }
  };
}

[[nodiscard]] Transform view_transform(const Tuple &from, const Tuple &to, const Tuple &up) {
  const auto forward = (to - from).normalize();
  const auto left = forward.cross(up.normalize());
  const auto true_up = left.cross(forward);
  const auto orientation = Transform{
      std::array<std::array<double, 4>, 4>{
          {{left.x(), left.y(), left.z(), 0.0},
           {true_up.x(), true_up.y(), true_up.z(), 0.0},
           {-forward.x(), -forward.y(), -forward.z(), 0.0},
           {0.0, 0.0, 0.0, 1.0}}
      }
  };
  return orientation * tf::translation(-from.x(), -from.y(), -from.z());
}
}
