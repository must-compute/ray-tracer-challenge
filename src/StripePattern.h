#ifndef RAY_TRACER_CHALLENGE_STRIPEPATTERN_H
#define RAY_TRACER_CHALLENGE_STRIPEPATTERN_H

#include "Color.h"
#include "Tuple.h"
#include "Transformations.h"
#include "Pattern.h"

class Shape;

class StripePattern final : public Pattern {
public:
  StripePattern(const Color &a, const Color &b);

  bool operator==(const StripePattern &other) const = default;

  [[nodiscard]] Color pattern_at(const Tuple &point) const override;

};

#endif //RAY_TRACER_CHALLENGE_STRIPEPATTERN_H