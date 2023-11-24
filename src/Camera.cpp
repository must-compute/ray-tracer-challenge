#include "Camera.h"

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
