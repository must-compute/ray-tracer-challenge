#include <gtest/gtest.h>

#include "Sphere.h"
#include "Material.h"
#include "Matrix.h"
#include "Transformations.h"

TEST(Sphere, SphereDefaultTransformation) {
  const auto s = Sphere{};
  const auto expected_transform = Matrix<4, 4>::identity();
  EXPECT_EQ(s.transform(), expected_transform);
}

TEST(Sphere, SphereSetTransform) {
  auto s = Sphere{};
  const auto t = tf::translation(2.0, 3.0, 4.0);
  s.set_transform(t);
  EXPECT_EQ(s.transform(), t);
}

TEST(Sphere, NormalAtPointOnAxisX) {
  const auto s = Sphere{};
  const auto n = s.normal_at(Point{1.0, 0.0, 0.0});
  EXPECT_EQ(n, (Vector{1.0, 0.0, 0.0}));
}

TEST(Sphere, NormalAtPointOnAxisY) {
  const auto s = Sphere{};
  const auto n = s.normal_at(Point{0.0, 1.0, 0.0});
  EXPECT_EQ(n, (Vector{0.0, 1.0, 0.0}));
}

TEST(Sphere, NormalAtPointOnAxisZ) {
  const auto s = Sphere{};
  const auto n = s.normal_at(Point{0.0, 0.0, 1.0});
  EXPECT_EQ(n, (Vector{0.0, 0.0, 1.0}));
}

TEST(Sphere, NormalAtPointOnNonAxialPoint) {
  const auto s = Sphere{};
  const auto loc = std::sqrt(3.0) / 3.0;
  const auto n = s.normal_at(Point{loc, loc, loc});
  EXPECT_EQ(n, (Vector{loc, loc, loc}));
}

TEST(Sphere, NormalIsNormalized) {
  const auto s = Sphere{};
  const auto loc = std::sqrt(3.0) / 3.0;
  const auto n = s.normal_at(Point{loc, loc, loc});
  EXPECT_EQ(n, n.normalize());
}

TEST(Sphere, ReflectingAt45Degrees) {
  const auto v = Vector{1.0, -1.0, 0.0};
  const auto n = Vector{0.0, 1.0, 0.0};
  const auto r = v.reflect(n);
  EXPECT_EQ(r, (Vector{1.0, 1.0, 0.0}));
}

TEST(Sphere, ReflectingSlanted) {
  const auto v = Vector{0.0, -1.0, 0.0};
  const double loc = std::sqrt(2.0) / 2.0;
  const auto n = Vector{loc, loc, 0.0};
  const auto r = v.reflect(n);
  EXPECT_EQ(r, (Vector{1.0, 0.0, 0.0}));
}

TEST(Sphere, SphereHasDefaultMaterial) {
  const auto s = Sphere{};
  const auto m = s.material();
  EXPECT_EQ(m, Material{});
}

TEST(Sphere, SphereMaterialAssignment) {
  auto s = Sphere{};
  auto m = Material{};
  m.ambient = 1.0;
  s.set_material(m);
  EXPECT_EQ(s.material(), m);
}

TEST(Sphere, HelperForProducingGlassSphere) {
  const auto sphere = make_glass_sphere();
  EXPECT_EQ(sphere.transform(), tf::Transform::identity());
  EXPECT_EQ(sphere.material().transparency, 1.0);
  EXPECT_EQ(sphere.material().refractive_index, 1.5);
}
