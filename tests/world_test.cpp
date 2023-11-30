#include <gtest/gtest.h>
#include <memory>
#include "Material.h"
#include "Sphere.h"
#include "PointLight.h"
#include "World.h"
#include "Ray.h"
#include "Plane.h"

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
    ASSERT_EQ(xs.size(), 4);
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
    ASSERT_GE(world.objects.size(), 2);
    const auto &shape = world.objects[1];
    const auto i = Intersection{0.5, shape};
    const auto comps = i.prepare_computations(ray);
    EXPECT_EQ(world.shade_hit(comps), make_color(0.90498, 0.90498, 0.90498));
}

TEST(World, ShadingWithAnIntersectionInShadow) {
    auto world = World{};
    world.light = PointLight{make_point(0.0, 0.0, -10.0), make_color(1.0, 1.0, 1.0)};
    const auto s1 = std::make_shared<Sphere>(Sphere{});
    auto s2 = std::make_shared<Sphere>(Sphere{});
    s2->set_transform(tf::translation(0.0, 0.0, 10.0));
    world.objects.push_back(s1);
    world.objects.push_back(s2);

    const auto ray = Ray{make_point(0.0, 0.0, 5.0), make_vector(0.0, 0.0, 1.0)};
    const auto i = Intersection{4.0, s2};
    const auto comps = i.prepare_computations(ray);
    const auto c = world.shade_hit(comps);
    EXPECT_EQ(c, make_color(0.1, 0.1, 0.1));
}

TEST(World, ColorWhenRayMisses) {
    auto world = make_default_world();
    const auto ray = Ray{make_point(0.0, 0.0, -5.0), make_vector(0.0, 1.0, 0.0)};
    EXPECT_EQ(world.color_at(ray), Color{});
}

TEST(World, ColorWhenRayHits) {
    auto world = make_default_world();
    const auto ray = Ray{make_point(0.0, 0.0, -5.0), make_vector(0.0, 0.0, 1.0)};
    EXPECT_EQ(world.color_at(ray), make_color(0.38066, 0.47583, 0.2855));
}

TEST(World, ColorWithIntersectionBehindTheRay) {
    // If the eye is inside two concentric spheres, check that we hit the inside of the inner sphere.
    // We set the ambient component to 1.0 because no light makes it into the insides.
    auto world = make_default_world();

    // Set the materials
    ASSERT_GE(world.objects.size(), 2);
    auto &outer = world.objects[0];
    auto &inner = world.objects[1];
    ASSERT_TRUE(outer);
    ASSERT_TRUE(inner);
    auto outer_m = outer->material();
    outer_m.ambient = 1.0;
    outer->set_material(outer_m);
    auto inner_m = inner->material();
    inner_m.ambient = 1.0;
    inner->set_material(inner_m);

    const auto ray = Ray{make_point(0.0, 0.0, 0.75), make_vector(0.0, 0.0, -1.0)};
    EXPECT_EQ(world.color_at(ray), inner_m.color);
}

TEST(World, NoShadowWhenNothingIsColinearWithPointAndLight) {
    const auto w = make_default_world();
    const auto p = make_point(0.0, 10.0, 0.0);
    EXPECT_FALSE(w.is_shadowed(p));
}

TEST(World, ShadowWhenAnObjectIsBetweenThePointAndTheLight) {
    const auto w = make_default_world();
    const auto p = make_point(10.0, -10.0, 10.0);
    EXPECT_TRUE(w.is_shadowed(p));
}

TEST(World, NoShadowWhenObjectIsBehindTheLight) {
    const auto w = make_default_world();
    const auto p = make_point(-20.0, 20.0, -20.0);
    EXPECT_FALSE(w.is_shadowed(p));
}

TEST(World, NoShadowWhenObjectIsBehindThePoint) {
    const auto w = make_default_world();
    const auto p = make_point(-2.0, 2.0, -2.0);
    EXPECT_FALSE(w.is_shadowed(p));
}

TEST(World, ReflectedColorForNonReflectiveMaterial) {
    const auto world = make_default_world();
    const auto ray = Ray{make_point(0.0, 0.0, 0.0), make_vector(0.0, 0.0, 1.0)};

    ASSERT_GE(world.objects.size(), 2);
    auto shape = world.objects[1];

    auto material = shape->material();
    material.ambient = 1.0;
    shape->set_material(material);

    const auto intersection = Intersection{1.0, shape};
    const auto comps = intersection.prepare_computations(ray);
    EXPECT_EQ(world.reflected_color(comps), make_color(0.0, 0.0, 0.0));
}

TEST(World, ReflectedColorForReflectiveMaterial) {
    auto world = make_default_world();

    auto material = Material{};
    material.reflective = 0.5;
    auto plane = std::make_shared<Plane>(Plane{});

    plane->set_material(material);
    plane->set_transform(tf::translation(0.0, -1.0, 0.0));

    world.objects.push_back(plane);

    const auto loc = std::sqrt(2.0) / 2.0;
    const auto ray = Ray{make_point(0.0, 0.0, -3.0), make_vector(0.0, -loc, loc)};
    const auto intersection = Intersection{std::sqrt(2.0), plane};

    const auto comps = intersection.prepare_computations(ray);
    EXPECT_EQ(world.reflected_color(comps), make_color(0.19032, 0.2379, 0.14274));
}

TEST(World, ShadeHitWithReflectiveMaterial) {
    auto world = make_default_world();

    auto material = Material{};
    material.reflective = 0.5;
    auto plane = std::make_shared<Plane>(Plane{});

    plane->set_material(material);
    plane->set_transform(tf::translation(0.0, -1.0, 0.0));

    world.objects.push_back(plane);

    const auto loc = std::sqrt(2.0) / 2.0;
    const auto ray = Ray{make_point(0.0, 0.0, -3.0), make_vector(0.0, -loc, loc)};
    const auto intersection = Intersection{std::sqrt(2.0), plane};

    const auto comps = intersection.prepare_computations(ray);
    EXPECT_EQ(world.shade_hit(comps), make_color(0.87677, 0.92436, 0.82918));
}

TEST(World, ColorAtWithMutuallyReflectiveSurfaces) {
    auto world = World{};
    world.light = PointLight{make_point(0.0, 0.0, 0.0), make_color(1.0, 1.0, 1.0)};

    auto plane_material = Material{};
    plane_material.reflective = 1.0;

    auto lower_plane = std::make_shared<Plane>(Plane{});
    lower_plane->set_material(plane_material);
    lower_plane->set_transform(tf::translation(0.0, -1.0, 0.0));

    auto upper_plane = std::make_shared<Plane>(Plane{});
    upper_plane->set_material(plane_material);
    upper_plane->set_transform(tf::translation(0.0, 1.0, 0.0));

    world.objects.push_back(lower_plane);
    world.objects.push_back(upper_plane);

    const auto ray = Ray{make_point(0.0, 0.0, 0.0), make_vector(0.0, 1.0, 0.0)};

    std::ignore = world.color_at(ray);
}

TEST(World, ReflectedColorAtMaxRecursiveDepth) {
    auto world = make_default_world();

    auto plane_material = Material{};
    plane_material.reflective = 0.5;

    auto plane = std::make_shared<Plane>(Plane{});
    plane->set_material(plane_material);
    plane->set_transform(tf::translation(0.0, -1.0, 0.0));

    world.objects.push_back(plane);

    const auto loc = std::sqrt(2.0) / 2.0;
    const auto ray = Ray{make_point(0.0, 0.0, -3.0), make_vector(0.0, -loc, loc)};
    const auto intersection = Intersection{std::sqrt(2.0), plane};
    const auto comps = intersection.prepare_computations(ray);

    EXPECT_EQ(world.reflected_color(comps, 0), make_color(0.0, 0.0, 0.0));
}
