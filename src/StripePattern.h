#ifndef RAY_TRACER_CHALLENGE_STRIPEPATTERN_H
#define RAY_TRACER_CHALLENGE_STRIPEPATTERN_H

#include "Color.h"
#include "Tuple.h"
#include "Transformations.h"

class Shape;

class StripePattern {
public:
    StripePattern();

    StripePattern(const Color &a, const Color &b);

    bool operator==(const StripePattern &other) const = default;

    [[nodiscard]] Color a() const;

    [[nodiscard]] Color b() const;

    [[nodiscard]] tf::Transform transform() const;

    void set_transform(const tf::Transform &t);

    [[nodiscard]] Color stripe_at(const Tuple &point) const;

    [[nodiscard]] Color stripe_at_object(const Shape &object, const Tuple &world_point) const;

private:
    Color a_;
    Color b_;
    tf::Transform transform_;
};


#endif //RAY_TRACER_CHALLENGE_STRIPEPATTERN_H