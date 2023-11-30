#include "World.h"
#include "Sphere.h"

[[nodiscard]] World make_default_world() {
    auto world = World{};
    const auto light = PointLight{make_point(-10.0, 10.0, -10.0), make_color(1.0, 1.0, 1.0)};
    auto material = Material{};

    material.color = make_color(0.8, 1.0, 0.6);
    material.diffuse = 0.7;
    material.specular = 0.2;

    auto s1 = Sphere{};
    s1.set_material(material);

    auto s2 = Sphere{};
    s2.set_transform(tf::scaling(0.5, 0.5, 0.5));

    world.objects.push_back(std::make_shared<Sphere>(std::move(s1)));
    world.objects.push_back(std::make_shared<Sphere>(std::move(s2)));
    world.light = std::make_optional(light);

    return world;
}

Intersections World::intersect(const Ray &ray) const {
    auto all_xs = Intersections{};
    for (const auto &obj: objects) {
        assert(obj);
        auto obj_xs = obj->intersect(ray);
        all_xs.insert(all_xs.end(), obj_xs.begin(), obj_xs.end());
    }

    std::sort(all_xs.begin(), all_xs.end());

    return all_xs;
}

// NOTE: These three functions (shade_hit, color_at, and reflected_color) have infinite recursion, but we break it by passing a decrementing "remaining" argument.
// We use these pragmas to get clang-tidy to suppress the infinite recursion warning.

Color World::shade_hit(const IntersectionComputation &comps, size_t remaining) const { // NOLINT
    // NOTE: without nudging the point away from the surface ever so slightly, tiny floating-point imprecisions would cause us to falsely intersect with ourselves and give a grainy shadow artifact called "acne".
    const bool in_shadow = is_shadowed(comps.over_point);

    if (light.has_value()) {
        assert(comps.object);
        const auto surface = comps.object->material().lighting(*comps.object, *light, comps.point, comps.eyev,
                                                               comps.normalv,
                                                               in_shadow);
        const auto reflected = reflected_color(comps, remaining);
        return surface + reflected;
    }
    return Color{};
}

[[nodiscard]] Color World::color_at(const Ray &ray, size_t remaining) const { // NOLINT
    const auto xs = intersect(ray);
    const auto maybe_hit = hit(xs);

    if (!maybe_hit.has_value()) {
        return Color{};
    }

    const auto comps = maybe_hit->prepare_computations(ray);
    return shade_hit(comps, remaining);
}

Color World::reflected_color(const IntersectionComputation &comps, size_t remaining) const { // NOLINT
    assert(comps.object);
    if (const auto reflectivity = comps.object->material().reflective; reflectivity > 0.0 && remaining > 0) {
        const auto ray = Ray{comps.over_point, comps.reflectv};
        return color_at(ray, remaining - 1) * reflectivity;
    } else {
        return make_color(0.0, 0.0, 0.0);
    }
}

bool World::is_shadowed(const Tuple &point) const {

    if (!light.has_value()) {
        return true;
    }

    const auto v = point - (light->position());
    const auto distance = v.magnitude();
    const auto ray = Ray{light->position(), v.normalize()};
    const auto intersections = intersect(ray);
    const auto maybe_hit = hit(intersections);
    if (maybe_hit.has_value() && maybe_hit->t < distance) {
        return true;
    }

    return false;
}

