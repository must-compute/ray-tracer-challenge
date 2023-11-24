#include "Camera.h"


Camera::Camera(const size_t hsize_in, const size_t vsize_in, const double field_of_view_in) :
        hsize(hsize_in),
        vsize(vsize_in),
        field_of_view(field_of_view_in),
        transform(tf::Transform::identity()) {
    // Calculate the pixel_size, half_width, and half_height given the field of view and h/v size.
    const double half_view = std::tan(field_of_view / 2.0);
    const auto aspect_ratio = static_cast<double>(hsize) / static_cast<double>(vsize);
    if (aspect_ratio >= 1.0) {
        half_width = half_view;
        half_height = half_view / aspect_ratio;
    } else {
        half_width = half_view * aspect_ratio;
        half_height = half_view;
    }
    pixel_size = (half_width * 2.0) / static_cast<double>(hsize);
}

size_t Camera::get_hsize() const {
    return hsize;
}

size_t Camera::get_vsize() const {
    return vsize;
}

double Camera::get_field_of_view() const {
    return field_of_view;
}

const tf::Transform &Camera::get_transform() const {
    return transform;
}

void Camera::set_transform(const tf::Transform &t) {
    transform = t;
}

double Camera::get_pixel_size() const {
    return pixel_size;
}

void Camera::set_pixel_size(double pixel_size_in) {
    pixel_size = pixel_size_in;
}
