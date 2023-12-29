#include <gtest/gtest.h>
#include <cmath>

#include "Material.h"
#include "Tuple.h"
#include "PointLight.h"
#include "StripePattern.h"
#include "Sphere.h"

TEST(Material, DefaultMaterial) {
  auto m = Material{};
  EXPECT_EQ(m.color, (Color{1.0, 1.0, 1.0}));
  EXPECT_EQ(m.ambient, 0.1);
  EXPECT_EQ(m.diffuse, 0.9);
  EXPECT_EQ(m.specular, 0.9);
  EXPECT_EQ(m.shininess, 200.0);

}

TEST(Material, LightingWithEyeBetweenLightAndSurface) {
  const auto s = Sphere{};
  const auto m = Material{};
  const auto position = make_point(0, 0, 0);

  const auto eyev = make_vector(0.0, 0.0, -1.0);
  const auto normalv = make_vector(0.0, 0.0, -1.0);
  const auto light = PointLight{make_point(0.0, 0.0, -10.0), Color{1.0, 1.0, 1.0}};
  const bool in_shadow = false;

  const auto result = m.lighting(s, light, position, eyev, normalv, in_shadow);
  EXPECT_EQ(result, (Color{1.9, 1.9, 1.9}));
}

TEST(Material, LightingWithEyeBetweenLightAndSurfaceWithEyeOffest45) {
  const auto s = Sphere{};
  const auto m = Material{};
  const auto position = make_point(0, 0, 0);

  const auto loc = std::sqrt(2.0) / 2.0;
  const auto eyev = make_vector(0.0, loc, loc);
  const auto normalv = make_vector(0.0, 0.0, -1.0);
  const auto light = PointLight{make_point(0.0, 0.0, -10.0), Color{1.0, 1.0, 1.0}};
  const bool in_shadow = false;

  const auto result = m.lighting(s, light, position, eyev, normalv, in_shadow);
  EXPECT_EQ(result, (Color{1.0, 1.0, 1.0}));
}

TEST(Material, LightingWithEyeOppositeSurfaceWithLightOffset45) {
  const auto s = Sphere{};
  const auto m = Material{};
  const auto position = make_point(0, 0, 0);

  const auto eyev = make_vector(0.0, 0.0, -1.0);
  const auto normalv = make_vector(0.0, 0.0, -1.0);
  const auto light = PointLight{make_point(0.0, 10.0, -10.0), Color{1.0, 1.0, 1.0}};
  const bool in_shadow = false;

  const auto result = m.lighting(s, light, position, eyev, normalv, in_shadow);
  EXPECT_EQ(result, (Color{0.7364, 0.7364, 0.7364}));
}

TEST(Material, LightingWithEyeInPathOfReflection) {
  const auto s = Sphere{};
  const auto m = Material{};
  const auto position = make_point(0, 0, 0);

  const auto loc = -std::sqrt(2.0) / 2.0;
  const auto eyev = make_vector(0.0, loc, loc);
  const auto normalv = make_vector(0.0, 0.0, -1.0);
  const auto light = PointLight{make_point(0.0, 10.0, -10.0), Color{1.0, 1.0, 1.0}};
  const bool in_shadow = false;

  const auto result = m.lighting(s, light, position, eyev, normalv, in_shadow);
  EXPECT_EQ(result, (Color{1.6364, 1.6364, 1.6364}));
}

TEST(Material, LightBehindSurface) {
  const auto s = Sphere{};
  const auto m = Material{};
  const auto position = make_point(0, 0, 0);

  const auto eyev = make_vector(0.0, 0.0, -1.0);
  const auto normalv = make_vector(0.0, 0.0, -1.0);
  const auto light = PointLight{make_point(0.0, 0.0, 10.0), Color{1.0, 1.0, 1.0}};
  const bool in_shadow = false;

  const auto result = m.lighting(s, light, position, eyev, normalv, in_shadow);
  EXPECT_EQ(result, (Color{0.1, 0.1, 0.1}));
}

TEST(Material, LightingWithSurfaceInShadow) {
  const auto s = Sphere{};
  const auto m = Material{};
  const auto position = make_point(0, 0, 0);

  const auto eyev = make_vector(0.0, 0.0, -1.0);
  const auto normalv = make_vector(0.0, 0.0, -1.0);
  const auto light = PointLight{make_point(0.0, 0.0, -10.0), Color{1.0, 1.0, 1.0}};
  const bool in_shadow = true;

  EXPECT_EQ(m.lighting(s, light, position, eyev, normalv, in_shadow), (Color{0.1, 0.1, 0.1}));
}

TEST(Material, LightingWithPatternApplied) {
  const auto s = Sphere{};
  auto m = Material{};
  m.pattern = std::make_unique<StripePattern>(StripePattern{Color{1.0, 1.0, 1.0}, Color{0.0, 0.0, 0.0}});
  m.ambient = 1.0;
  m.diffuse = 0.0;
  m.specular = 0.0;

  const auto eyev = make_vector(0.0, 0.0, -1.0);
  const auto normalv = make_vector(0.0, 0.0, -1.0);
  const auto light = PointLight{make_point(0.0, 0.0, -10.0), Color{1.0, 1.0, 1.0}};

  const bool in_shadow = false;
  const auto c1 = m.lighting(s, light, make_point(0.9, 0.0, 0.0), eyev, normalv, in_shadow);
  const auto c2 = m.lighting(s, light, make_point(1.1, 0.0, 0.0), eyev, normalv, in_shadow);

  EXPECT_EQ(c1, (Color{1.0, 1.0, 1.0}));
  EXPECT_EQ(c2, (Color{0.0, 0.0, 0.0}));
}

TEST(Material, ReflectivityForDefaultMaterial) {
  auto m = Material{};
  EXPECT_EQ(m.reflective, 0.0);
}

TEST(Material, TransparencyAndRefractiveIndexForDefaultMaterial) {
  auto m = Material{};
  EXPECT_EQ(m.transparency, 0.0);
  EXPECT_EQ(m.refractive_index, 1.0);
}
