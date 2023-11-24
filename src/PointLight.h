#ifndef RAY_TRACER_CHALLENGE_POINTLIGHT_H
#define RAY_TRACER_CHALLENGE_POINTLIGHT_H

#include "Tuple.h"
#include "Color.h"

class PointLight {
public:
    PointLight(const Tuple &position, const Color &intensity) : intensity_{intensity}, position_{position} {}

    [[nodiscard]] Color intensity() const;

    [[nodiscard]] Tuple position() const;

    bool operator==(const PointLight &other) const = default;


private:
    Color intensity_;
    Tuple position_;
};


#endif //RAY_TRACER_CHALLENGE_POINTLIGHT_H
