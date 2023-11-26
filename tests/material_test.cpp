#include <gtest/gtest.h>
#include <cmath>

#include "Material.h"
#include "Tuple.h"
#include "PointLight.h"
#include "StripePattern.h"


TEST(Material, DefaultMaterial) {
    auto m = Material{};
    EXPECT_EQ(m.color, make_color(1.0, 1.0, 1.0));
    EXPECT_EQ(m.ambient, 0.1);
    EXPECT_EQ(m.diffuse, 0.9);
    EXPECT_EQ(m.specular, 0.9);
    EXPECT_EQ(m.shininess, 200.0);

}

TEST(Material, LightingWithEyeBetweenLightAndSurface) {
    const auto m = Material{};
    const auto position = make_point(0, 0, 0);

    const auto eyev = make_vector(0.0, 0.0, -1.0);
    const auto normalv = make_vector(0.0, 0.0, -1.0);
    const auto light = PointLight{make_point(0.0, 0.0, -10.0), make_color(1.0, 1.0, 1.0)};
    const bool in_shadow = false;

    const auto result = m.lighting(light, position, eyev, normalv, in_shadow);
    EXPECT_EQ(result, make_color(1.9, 1.9, 1.9));
}

TEST(Material, LightingWithEyeBetweenLightAndSurfaceWithEyeOffest45) {
    const auto m = Material{};
    const auto position = make_point(0, 0, 0);

    const auto loc = std::sqrt(2.0) / 2.0;
    const auto eyev = make_vector(0.0, loc, loc);
    const auto normalv = make_vector(0.0, 0.0, -1.0);
    const auto light = PointLight{make_point(0.0, 0.0, -10.0), make_color(1.0, 1.0, 1.0)};
    const bool in_shadow = false;

    const auto result = m.lighting(light, position, eyev, normalv, in_shadow);
    EXPECT_EQ(result, make_color(1.0, 1.0, 1.0));
}

TEST(Material, LightingWithEyeOppositeSurfaceWithLightOffset45) {
    const auto m = Material{};
    const auto position = make_point(0, 0, 0);

    const auto eyev = make_vector(0.0, 0.0, -1.0);
    const auto normalv = make_vector(0.0, 0.0, -1.0);
    const auto light = PointLight{make_point(0.0, 10.0, -10.0), make_color(1.0, 1.0, 1.0)};
    const bool in_shadow = false;

    const auto result = m.lighting(light, position, eyev, normalv, in_shadow);
    EXPECT_EQ(result, make_color(0.7364, 0.7364, 0.7364));
}

TEST(Material, LightingWithEyeInPathOfReflection) {
    const auto m = Material{};
    const auto position = make_point(0, 0, 0);

    const auto loc = -std::sqrt(2.0) / 2.0;
    const auto eyev = make_vector(0.0, loc, loc);
    const auto normalv = make_vector(0.0, 0.0, -1.0);
    const auto light = PointLight{make_point(0.0, 10.0, -10.0), make_color(1.0, 1.0, 1.0)};
    const bool in_shadow = false;

    const auto result = m.lighting(light, position, eyev, normalv, in_shadow);
    EXPECT_EQ(result, make_color(1.6364, 1.6364, 1.6364));
}

TEST(Material, LightBehindSurface) {
    const auto m = Material{};
    const auto position = make_point(0, 0, 0);

    const auto eyev = make_vector(0.0, 0.0, -1.0);
    const auto normalv = make_vector(0.0, 0.0, -1.0);
    const auto light = PointLight{make_point(0.0, 0.0, 10.0), make_color(1.0, 1.0, 1.0)};
    const bool in_shadow = false;

    const auto result = m.lighting(light, position, eyev, normalv, in_shadow);
    EXPECT_EQ(result, make_color(0.1, 0.1, 0.1));
}

TEST(Material, LightingWithSurfaceInShadow) {
    const auto m = Material{};
    const auto position = make_point(0, 0, 0);

    const auto eyev = make_vector(0.0, 0.0, -1.0);
    const auto normalv = make_vector(0.0, 0.0, -1.0);
    const auto light = PointLight{make_point(0.0, 0.0, -10.0), make_color(1.0, 1.0, 1.0)};
    const bool in_shadow = true;

    EXPECT_EQ(m.lighting(light, position, eyev, normalv, in_shadow), make_color(0.1, 0.1, 0.1));
}

TEST(Material, LightingWithPatternApplied) {
    auto m = Material{};
    m.pattern = StripePattern{make_color(1.0, 1.0, 1.0), make_color(0.0, 0.0, 0.0)};
    m.ambient = 1.0;
    m.diffuse = 0.0;
    m.specular = 0.0;

    const auto eyev = make_vector(0.0, 0.0, -1.0);
    const auto normalv = make_vector(0.0, 0.0, -1.0);
    const auto light = PointLight{make_point(0.0, 0.0, -10.0), make_color(1.0, 1.0, 1.0)};

    const bool in_shadow = false;
    const auto c1 = m.lighting(light, make_point(0.9, 0.0, 0.0), eyev, normalv, in_shadow);
    const auto c2 = m.lighting(light, make_point(1.1, 0.0, 0.0), eyev, normalv, in_shadow);

    EXPECT_EQ(c1, make_color(1.0, 1.0, 1.0));
    EXPECT_EQ(c2, make_color(0.0, 0.0, 0.0));
}
