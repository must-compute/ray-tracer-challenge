
#include "Intersection.h"
#include "Ray.h"
#include "Shape.h"
#include <algorithm>

std::optional<Intersection> hit(const Intersections &intersections) {
    // Return the intersection with the smallest non-negative t. Negative ts don't count because they're behind the ray origin.
    Intersections nonnegative{};
    std::copy_if(intersections.begin(), intersections.end(), std::back_inserter(nonnegative),
                 [](const Intersection &i) { return i.t >= 0.0; });

    const auto iter = std::min_element(nonnegative.begin(), nonnegative.end(),
                                       [](const Intersection &a, const Intersection &b) { return a.t < b.t; });
    if (iter != nonnegative.end()) {
        return *iter;
    }
    return std::nullopt;
}

IntersectionComputation Intersection::prepare_computations(const Ray &ray, const Intersections &xs) const {
    auto comps = IntersectionComputation{};

    assert(object);
    comps.t = t;
    comps.object = object;
    comps.point = ray.position_at_t(comps.t);
    comps.eyev = -ray.direction();
    comps.normalv = comps.object->normal_at(comps.point);

    if (comps.normalv.dot(comps.eyev) < 0) {
        comps.inside = true;
        comps.normalv = -comps.normalv;
    } else {
        comps.inside = false;
    }

    comps.reflectv = ray.direction().reflect(comps.normalv);

    comps.over_point = comps.point + (comps.normalv * EPSILON);
    comps.under_point = comps.point - (comps.normalv * EPSILON);

    // Compute the refractive indices (n1 and n2).
    std::vector<std::shared_ptr<Shape>> seen_objects{};
    Intersections xs_to_check{xs};
    if (xs_to_check.empty()) {
        xs_to_check.push_back(*this);
    }
    for (const auto &i: xs_to_check) {
        // Set n1 if this intersection is the hit.
        if (i == *this) {
            if (seen_objects.empty()) {
                comps.n1 = 1.0;
            } else {
                assert(seen_objects.back());
                comps.n1 = seen_objects.back()->material().refractive_index;
            }
        }

        if (std::find(seen_objects.begin(), seen_objects.end(), i.object) != seen_objects.end()) {
            // If we've seen this object before, delete it (we're exiting it).
            seen_objects.erase(std::remove(seen_objects.begin(), seen_objects.end(), i.object), seen_objects.end());
        } else {
            // Otherwise, add this seen object (we're entering it).
            seen_objects.push_back(i.object);
        }

        // Set n2 and break if this intersection is a hit.
        if (i == *this) {
            if (seen_objects.empty()) {
                comps.n2 = 1.0;
            } else {
                assert(seen_objects.back());
                comps.n2 = seen_objects.back()->material().refractive_index;
            }

            break;
        }
    }

    return comps;
}
