#include <gtest/gtest.h>
#include "Material.h"
#include "Sphere.h"
#include "PointLight.h"
#include "World.h"

TEST(World, CreatingWorld) {
    const auto w = World{};
    EXPECT_TRUE(w.objects.empty());
    EXPECT_FALSE(w.light.has_value());
}

TEST(World, CreatingDefaultWorld) {
    const auto light = PointLight{make_point(-10.0, 10.0, -10.0), make_color(1.0, 1.0, 1.0)};
    auto material = Material{};
    material.color = make_color(0.8, 1.0, 0.6);
    material.diffuse = 0.7;
    material.specular = 0.2;
    auto s1 = Sphere{};
    s1.set_material(material);
    auto s2 = Sphere{};
    s2.set_transform(tf::scaling(0.5, 0.5, 0.5));
    const auto world = make_default_world();
    EXPECT_TRUE(world.light.has_value());
    EXPECT_EQ(*world.light, light);
}
