#include <gtest/gtest.h>
#include <cmath>

#include "Material.h"
#include "Tuple.h"
#include "PointLight.h"

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

    const auto result = m.lighting(light, position, eyev, normalv);
    EXPECT_EQ(result, make_color(1.9, 1.9, 1.9));
}

TEST(Material, LightingWithEyeBetweenLightAndSurfaceWithEyeOffest45) {
    const auto m = Material{};
    const auto position = make_point(0, 0, 0);

    const auto loc = std::sqrt(2.0) / 2.0;
    const auto eyev = make_vector(0.0, loc, loc);
    const auto normalv = make_vector(0.0, 0.0, -1.0);
    const auto light = PointLight{make_point(0.0, 0.0, -10.0), make_color(1.0, 1.0, 1.0)};

    const auto result = m.lighting(light, position, eyev, normalv);
    EXPECT_EQ(result, make_color(1.0, 1.0, 1.0));
}

TEST(Material, LightingWithEyeOppositeSurfaceWithLightOffset45) {
    const auto m = Material{};
    const auto position = make_point(0, 0, 0);

    const auto eyev = make_vector(0.0, 0.0, -1.0);
    const auto normalv = make_vector(0.0, 0.0, -1.0);
    const auto light = PointLight{make_point(0.0, 10.0, -10.0), make_color(1.0, 1.0, 1.0)};

    const auto result = m.lighting(light, position, eyev, normalv);
    EXPECT_EQ(result, make_color(0.7364, 0.7364, 0.7364));
}

TEST(Material, LightingWithEyeInPathOfReflection) {
    const auto m = Material{};
    const auto position = make_point(0, 0, 0);

    const auto loc = -std::sqrt(2.0) / 2.0;
    const auto eyev = make_vector(0.0, loc, loc);
    const auto normalv = make_vector(0.0, 0.0, -1.0);
    const auto light = PointLight{make_point(0.0, 10.0, -10.0), make_color(1.0, 1.0, 1.0)};

    const auto result = m.lighting(light, position, eyev, normalv);
    EXPECT_EQ(result, make_color(1.6364, 1.6364, 1.6364));
}

TEST(Material, LightBehindSurface) {
    const auto m = Material{};
    const auto position = make_point(0, 0, 0);

    const auto eyev = make_vector(0.0, 0.0, -1.0);
    const auto normalv = make_vector(0.0, 0.0, -1.0);
    const auto light = PointLight{make_point(0.0, 0.0, 10.0), make_color(1.0, 1.0, 1.0)};

    const auto result = m.lighting(light, position, eyev, normalv);
    EXPECT_EQ(result, make_color(0.1, 0.1, 0.1));
}
