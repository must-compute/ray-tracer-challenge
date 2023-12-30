#ifndef RAY_TRACER_CHALLENGE_CHECKERPATTERN_H
#define RAY_TRACER_CHALLENGE_CHECKERPATTERN_H

#include "Pattern.h"

class CheckerPattern final : public Pattern {
public:
  CheckerPattern(const Color &a, const Color &b);

  [[nodiscard]] Color pattern_at(const Point &point) const override;
};

#endif //RAY_TRACER_CHALLENGE_CHECKERPATTERN_H
