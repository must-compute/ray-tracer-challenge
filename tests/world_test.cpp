#include <gtest/gtest.h>
#include "Material.h"
#include "Sphere.h"
#include "PointLight.h"
#include "World.h"
#include "Ray.h"

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

TEST(World, IntersectWorldWithRay) {
    const auto world = make_default_world();
    const auto ray = Ray{make_point(0.0, 0.0, -5.0), make_vector(0.0, 0.0, 1.0)};
    const auto xs = world.intersect(ray);
    EXPECT_EQ(xs.size(), 4);
    EXPECT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[1].t, 4.5);
    EXPECT_EQ(xs[2].t, 5.5);
    EXPECT_EQ(xs[3].t, 6);
}

TEST(World, ShadingAnIntersection) {
    const auto world = make_default_world();
    const auto ray = Ray{make_point(0.0, 0.0, -5.0), make_vector(0.0, 0.0, 1.0)};
    EXPECT_FALSE(world.objects.empty());
    const auto &shape = world.objects.front();
    const auto i = Intersection{4.0, shape};
    const auto comps = i.prepare_computations(ray);
    EXPECT_EQ(world.shade_hit(comps), make_color(0.38066, 0.47583, 0.2855));
}

TEST(World, ShadingAnIntersectionFromTheInside) {
    auto world = make_default_world();
    world.light = PointLight{make_point(0.0, 0.25, 0.0), make_color(1.0, 1.0, 1.0)};
    const auto ray = Ray{make_point(0.0, 0.0, 0.0), make_vector(0.0, 0.0, 1.0)};
    EXPECT_GE(world.objects.size(), 2);
    const auto &shape = world.objects[1];
    const auto i = Intersection{0.5, shape};
    const auto comps = i.prepare_computations(ray);
    EXPECT_EQ(world.shade_hit(comps), make_color(0.90498, 0.90498, 0.90498));
}
