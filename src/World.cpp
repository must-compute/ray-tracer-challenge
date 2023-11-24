#include "World.h"

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

    world.objects.push_back(s1);
    world.objects.push_back(s2);
    world.light = std::make_optional(light);

    return world;
}

Intersections World::intersect(const Ray &ray) const {
    auto all_xs = Intersections{};
    for (auto obj: objects) {
        auto obj_xs = ray.intersect(obj);
        all_xs.insert(all_xs.end(), obj_xs.begin(), obj_xs.end());
    }

    std::sort(all_xs.begin(), all_xs.end());

    return all_xs;
}

Color World::shade_hit(const IntersectionComputation &comps) const {
    if (light.has_value()) {
        return comps.object.material().lighting(*light, comps.point, comps.eyev, comps.normalv);
    }
    return Color{};
}
