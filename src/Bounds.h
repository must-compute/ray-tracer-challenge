#ifndef BOUNDS_H
#define BOUNDS_H

#include <iostream>

#include "Tuple.h"

// TODO add a debug-mode render function to show the wireframe bounding box
class Bounds {
public:
    Bounds() = default;

    Bounds(const Tuple &minimum, const Tuple &maximum);

private:
    Tuple minimum_{};
    Tuple maximum_{};
};

#endif //BOUNDS_H
