#include "Tuple.h"


[[nodiscard]] Tuple make_point(double x, double y, double z) {
    return {x, y, z, 1.0};
}

[[nodiscard]] Tuple make_vector(double x, double y, double z) {
    return {x, y, z, 0.0};
}

