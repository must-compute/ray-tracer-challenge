#include "Tuple.h"

// TODO replace all usages of these factories with the updated constructors

Point make_point(double x, double y, double z) {
  return Point{x, y, z};
}

Vector make_vector(double x, double y, double z) {
  return Vector{x, y, z};
}
