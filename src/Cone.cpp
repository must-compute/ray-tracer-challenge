#include "Cone.h"
#include <numbers>

[[nodiscard]] bool is_ray_cap_intersecting(const Ray &ray, double t, double cap_y) {
    const auto x = ray.origin().x() + t * ray.direction().x();
    const auto z = ray.origin().z() + t * ray.direction().z();
    return (std::pow(x, 2) + std::pow(z, 2)) <= std::abs(cap_y);
}

double Cone::minimum() const {
    return minimum_;
}

double Cone::maximum() const {
    return maximum_;
}

void Cone::set_minimum(double min) {
    minimum_ = min;
}

void Cone::set_maximum(double max) {
    maximum_ = max;
}

bool Cone::closed() const {
    return closed_;
}

void Cone::set_closed(bool closed) {
    closed_ = closed;
}

Intersections Cone::local_intersect(const Ray &ray) {
    const auto a =
            std::pow(ray.direction().x(), 2) - std::pow(ray.direction().y(), 2) + std::pow(ray.direction().z(), 2);
    Intersections xs{};
    intersect_caps(ray, xs);

    const auto b = 2 * ray.origin().x() * ray.direction().x() -
                   2 * ray.origin().y() * ray.direction().y() +
                   2 * ray.origin().z() * ray.direction().z();
    const auto c = std::pow(ray.origin().x(), 2) - std::pow(ray.origin().y(), 2) + std::pow(ray.origin().z(), 2);

    // Ray is parallel to one of the cone's halves
    if (within_epsilon(a, 0)) {
        if (within_epsilon(b, 0)) {
            // If b is also zero, it's a miss.
            return {};
        } else {
            // Otherwise, we intersect at a single point.
            xs.push_back(Intersection{-c / (2 * b), this});
            return xs;
        }
    }

    const auto discriminant = std::pow(b, 2) - 4 * a * c;

    // Ray does not intersect the cone
    if (discriminant < 0) {
        return {};
    }

    const auto t0 = (-b - std::sqrt(discriminant)) / (2 * a);
    const auto t1 = (-b + std::sqrt(discriminant)) / (2 * a);

    const auto y0 = ray.origin().y() + (t0 * ray.direction().y());
    const auto y1 = ray.origin().y() + (t1 * ray.direction().y());

    if (minimum_ < y0 && y0 < maximum_) {
        xs.push_back(Intersection{t0, this});
    }

    if (minimum_ < y1 && y1 < maximum_) {
        xs.push_back(Intersection{t1, this});
    }

    return xs;
}

Tuple Cone::local_normal_at(const Tuple &point_in_object_space) const {
    auto dist = std::sqrt(std::pow(point_in_object_space.x(), 2) + std::pow(point_in_object_space.z(), 2));

    if (point_in_object_space.y() > 0.0) {
        dist = -dist;
    }

    return make_vector(point_in_object_space.x(), dist, point_in_object_space.z());
}

void Cone::intersect_caps(const Ray &ray, Intersections &xs) const {
    if (!closed_) {
        return;
    }

    // check lower cap
    auto t = (minimum_ - ray.origin().y()) / ray.direction().y();
    if (is_ray_cap_intersecting(ray, t, minimum_)) {
        xs.push_back(Intersection{t, this});
    }

    // check upper cap
    t = (maximum_ - ray.origin().y()) / ray.direction().y();
    if (is_ray_cap_intersecting(ray, t, maximum_)) {
        xs.push_back(Intersection{t, this});
    }
}

BoundingBox Cone::make_bounding_box() const {
    const auto limit = std::max(std::abs(minimum_), std::abs(maximum_));
    return {make_point(-limit, minimum_, -limit), make_point(limit, maximum_, limit)};
}
