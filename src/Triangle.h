#ifndef RAY_TRACER_CHALLENGE_TRIANGLE_H
#define RAY_TRACER_CHALLENGE_TRIANGLE_H


#include "Shape.h"
#include "Tuple.h"

class Triangle final : public Shape {
public:
    Triangle(const Tuple &p1, const Tuple &p2, const Tuple &p3);

    bool operator==(const Triangle &other) const = default;

    [[nodiscard]] Intersections local_intersect(const Ray &ray) override;

    [[nodiscard]] Tuple local_normal_at(const Tuple &point_in_object_space) const override;

    [[nodiscard]] BoundingBox make_bounding_box() const override;

    [[nodiscard]] Tuple p1() const;

    [[nodiscard]] Tuple p2() const;

    [[nodiscard]] Tuple p3() const;

    [[nodiscard]] Tuple e1() const;

    [[nodiscard]] Tuple e2() const;

    [[nodiscard]] Tuple normal() const;

private:
    Tuple p1_{};
    Tuple p2_{};
    Tuple p3_{};
    Tuple e1_{};
    Tuple e2_{};
    Tuple normal_{};
};


#endif //RAY_TRACER_CHALLENGE_TRIANGLE_H
