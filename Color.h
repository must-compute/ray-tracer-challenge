#ifndef RAY_TRACER_CHALLENGE_COLOR_H
#define RAY_TRACER_CHALLENGE_COLOR_H

#include "BaseTuple.h"

using Color = BaseTuple<TupleOrColor::COLOR>;

[[nodiscard]] Color make_color(double red, double green, double blue);

#endif //RAY_TRACER_CHALLENGE_COLOR_H
