#ifndef RAY_TRACER_CHALLENGE_TESTPATTERN_H
#define RAY_TRACER_CHALLENGE_TESTPATTERN_H

#include "Pattern.h"

class TestPattern final : public Pattern {
public:
  [[nodiscard]] Color pattern_at(const Tuple &point) const override;
};

#endif //RAY_TRACER_CHALLENGE_TESTPATTERN_H
