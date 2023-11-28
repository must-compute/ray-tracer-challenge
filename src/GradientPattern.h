#ifndef RAY_TRACER_CHALLENGE_GRADIENTPATTERN_H
#define RAY_TRACER_CHALLENGE_GRADIENTPATTERN_H

#include "Pattern.h"


class GradientPattern final : public Pattern {
public:
    GradientPattern(const Color &a, const Color &b);

    [[nodiscard]] Color pattern_at(const Tuple &point) const override;
};


#endif //RAY_TRACER_CHALLENGE_GRADIENTPATTERN_H
