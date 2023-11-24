#ifndef RAY_TRACER_CHALLENGE_CAMERA_H
#define RAY_TRACER_CHALLENGE_CAMERA_H

#include <cstddef>
#include "Transformations.h"

class Camera {

public:
    Camera(size_t hsize_in, size_t vsize_in, double field_of_view_in);

    [[nodiscard]] size_t get_hsize() const;

    [[nodiscard]] size_t get_vsize() const;

    [[nodiscard]] double get_field_of_view() const;

    [[nodiscard]] const tf::Transform &get_transform() const;

    void set_transform(const tf::Transform &t);

    [[nodiscard]] double get_pixel_size() const;

    void set_pixel_size(double pixel_size_in);

private:
    size_t hsize;
    size_t vsize;
    double field_of_view;
    tf::Transform transform;
    // The size of each pixel in world units.
    double pixel_size;
    // The size of half the canvas width in world units.
    double half_width;
    // The size of half the canvas height in world units.
    double half_height;
};

#endif //RAY_TRACER_CHALLENGE_CAMERA_H