#ifndef RAY_TRACER_CHALLENGE_TUPLE_H
#define RAY_TRACER_CHALLENGE_TUPLE_H


struct Tuple {
    double x, y, z, w;

    Tuple(double x, double y, double z, double w);

    [[nodiscard]] bool is_point() const { return w == 1.0; }

    [[nodiscard]] bool is_vector() const { return w == 0.0; }
};


#endif //RAY_TRACER_CHALLENGE_TUPLE_H
