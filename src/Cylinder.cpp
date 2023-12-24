#include "Cylinder.h"

// helper function to check if intersection at t is within a radius of 1.0 from the y-axis.
[[nodiscard]] bool is_ray_cap_intersecting(const Ray &ray, double t) {
    const auto x = ray.origin().x() + t * ray.direction().x();
    const auto z = ray.origin().z() + t * ray.direction().z();
    return (std::pow(x, 2) + std::pow(z, 2)) <= 1.0;
}

double Cylinder::minimum() const {
    return minimum_;
}

double Cylinder::maximum() const {
    return maximum_;
}

void Cylinder::set_minimum(double min) {
    minimum_ = min;
}

void Cylinder::set_maximum(double max) {
    maximum_ = max;
}

Tuple Cylinder::local_normal_at(const Tuple &point_in_object_space) const {
    // square of the distance from the y-axis
    const auto dist = std::pow(point_in_object_space.x(), 2) + std::pow(point_in_object_space.z(), 2);

    if (dist < 1 && point_in_object_space.y() >= maximum_ - EPSILON) { // ON TOP CAP
        return make_vector(0.0, 1.0, 0.0);
    } else if (dist < 1 && point_in_object_space.y() >= minimum_ - EPSILON) { // ON BOTTOM CAP
        return make_vector(0.0, -1.0, 0.0);
    } else { // ON CYLINDER
        return make_vector(point_in_object_space.x(), 0.0, point_in_object_space.z());
    }
}


[[nodiscard]] Intersections Cylinder::local_intersect(const Ray &ray) {
    const auto a = std::pow(ray.direction().x(), 2) + std::pow(ray.direction().z(), 2);
    Intersections xs{};
    intersect_caps(ray, xs);

    // Ray is parallel to the y-axis, so we only need to check intersections on caps;
    if (std::abs(a) < EPSILON) {
        return xs;
    }

    const auto b = 2 * ray.origin().x() * ray.direction().x() +
                   2 * ray.origin().z() * ray.direction().z();
    const auto c = std::pow(ray.origin().x(), 2) + std::pow(ray.origin().z(), 2) - 1.0;

    const auto discriminant = std::pow(b, 2) - 4 * a * c;

    // Ray does not intersect the cylinder
    if (discriminant < 0) {
        return {};
    }

    const auto t0 = (-b - std::sqrt(discriminant)) / (2 * a);
    const auto t1 = (-b + std::sqrt(discriminant)) / (2 * a);
    const auto cylinder = std::make_shared<Cylinder>(*this);

    const auto y0 = ray.origin().y() + (t0 * ray.direction().y());
    const auto y1 = ray.origin().y() + (t1 * ray.direction().y());

    if (minimum_ < y0 && y0 < maximum_) {
        xs.push_back(Intersection{t0, cylinder});
    }

    if (minimum_ < y1 && y1 < maximum_) {
        xs.push_back(Intersection{t1, cylinder});
    }

    return xs;
}

bool Cylinder::closed() const {
    return closed_;
}

void Cylinder::set_closed(bool closed) {
    closed_ = closed;
}

void Cylinder::intersect_caps(const Ray &ray, Intersections &xs) const {
    // caps only matter if the cylinder is closed and might be intersected by the ray (i.e. ray not parallel to the cap)
    if ((!closed_) || within_epsilon(ray.direction().y(), 0.0)) {
        return;
    }

    const auto shared_cylinder = std::make_shared<Cylinder>(*this);

    // check lower cap
    auto t = (minimum_ - ray.origin().y()) / ray.direction().y();
    if (is_ray_cap_intersecting(ray, t)) {
        xs.push_back(Intersection{t, shared_cylinder});
    }

    // check upper cap
    t = (maximum_ - ray.origin().y()) / ray.direction().y();
    if (is_ray_cap_intersecting(ray, t)) {
        xs.push_back(Intersection{t, shared_cylinder});
    }
}

BoundingBox Cylinder::make_bounding_box() const {
    return {make_point(-1.0, minimum(), -1.0), make_point(1.0, maximum(), 1.0)};
}
