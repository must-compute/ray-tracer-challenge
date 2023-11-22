
#include "Sphere.h"

tf::Transform Sphere::transform() const {
    return transform_;
}

void Sphere::set_transform(const tf::Transform &tf_in) {
    transform_ = tf_in;
}
