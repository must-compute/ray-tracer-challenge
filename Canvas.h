
#ifndef RAY_TRACER_CHALLENGE_CANVAS_H
#define RAY_TRACER_CHALLENGE_CANVAS_H


#include <cstddef>
#include <array>
#include "Color.h"

template<size_t WIDTH, size_t HEIGHT>
class Canvas {
public:
    [[nodiscard]] consteval size_t width() const {
        return WIDTH;
    }

    [[nodiscard]] consteval size_t height() const {
        return HEIGHT;
    }

    std::array<std::array<Color, WIDTH>, HEIGHT> pixels() const {
        return pixels_;
    }

private:
    std::array<std::array<Color, WIDTH>, HEIGHT> pixels_;
    //std::vector<std::vector<Color>> pixels;

};


#endif //RAY_TRACER_CHALLENGE_CANVAS_H
