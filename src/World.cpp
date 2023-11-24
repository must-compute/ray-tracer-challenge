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
