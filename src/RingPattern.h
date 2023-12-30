#ifndef RAY_TRACER_CHALLENGE_RINGPATTERN_H
#define RAY_TRACER_CHALLENGE_RINGPATTERN_H

#include "Pattern.h"

class RingPattern final : public Pattern {
public:
  RingPattern(const Color &a, const Color &b);

  [[nodiscard]] Color pattern_at(const Point &point) const override;
};

#endif //RAY_TRACER_CHALLENGE_RINGPATTERN_H
