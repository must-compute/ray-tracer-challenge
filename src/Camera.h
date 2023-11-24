#ifndef RAY_TRACER_CHALLENGE_CAMERA_H
#define RAY_TRACER_CHALLENGE_CAMERA_H

#include <cstddef>
#include "Transformations.h"

class Camera {

public:
    Camera(const size_t hsize_in, const size_t vsize_in, const double field_of_view_in) :
            hsize(hsize_in),
            vsize(vsize_in),
            field_of_view(field_of_view_in),
            transform(tf::Transform::identity()) {
        // TODO initialize pixel_size properly
        pixel_size = 0.0;
    }

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
    double pixel_size;
};

#endif //RAY_TRACER_CHALLENGE_CAMERA_H