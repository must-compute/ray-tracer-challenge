#ifndef RAY_TRACER_CHALLENGE_TUPLE_H
#define RAY_TRACER_CHALLENGE_TUPLE_H

#include "util.h"
#include "BaseTuple.h"

using Tuple = BaseTuple<TupleOrColor::TUPLE>;

// TODO this prevents implicit conversion for params. Not sure if it's idiomatic.
template<typename T>
Tuple make_point(T x, T y, T z) = delete;

Tuple make_point(double x, double y, double z);

Tuple make_vector(double x, double y, double z);

#endif //RAY_TRACER_CHALLENGE_TUPLE_H