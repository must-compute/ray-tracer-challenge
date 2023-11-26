#ifndef RAY_TRACER_CHALLENGE_STRIPEPATTERN_H
#define RAY_TRACER_CHALLENGE_STRIPEPATTERN_H

#include "Color.h"
#include "Tuple.h"

class StripePattern {
public:
    StripePattern();

    StripePattern(const Color &a, const Color &b);

    bool operator==(const StripePattern &other) const = default;

    [[nodiscard]] Color a() const;

    [[nodiscard]] Color b() const;

    [[nodiscard]] Color stripe_at(const Tuple &point) const;

private:
    Color a_;
    Color b_;
};


#endif //RAY_TRACER_CHALLENGE_STRIPEPATTERN_H