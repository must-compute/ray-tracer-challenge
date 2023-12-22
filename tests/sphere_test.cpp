#include <gtest/gtest.h>
#include <numbers>

#include "Sphere.h"
#include "Material.h"
#include "Matrix.h"
#include "Transformations.h"
#include "Group.h"

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
    const auto n = s.normal_at(make_point(1.0, 0.0, 0.0));
    EXPECT_EQ(n, make_vector(1.0, 0.0, 0.0));
}

TEST(Sphere, NormalAtPointOnAxisY) {
    const auto s = Sphere{};
    const auto n = s.normal_at(make_point(0.0, 1.0, 0.0));
    EXPECT_EQ(n, make_vector(0.0, 1.0, 0.0));
}

TEST(Sphere, NormalAtPointOnAxisZ) {
    const auto s = Sphere{};
    const auto n = s.normal_at(make_point(0.0, 0.0, 1.0));
    EXPECT_EQ(n, make_vector(0.0, 0.0, 1.0));
}

TEST(Sphere, NormalAtPointOnNonAxialPoint) {
    const auto s = Sphere{};
    const auto loc = std::sqrt(3.0) / 3.0;
    const auto n = s.normal_at(make_point(loc, loc, loc));
    EXPECT_EQ(n, make_vector(loc, loc, loc));
}

TEST(Sphere, NormalIsNormalized) {
    const auto s = Sphere{};
    const auto loc = std::sqrt(3.0) / 3.0;
    const auto n = s.normal_at(make_point(loc, loc, loc));
    EXPECT_EQ(n, n.normalize());
}

TEST(Sphere, ReflectingAt45Degrees) {
    const auto v = make_vector(1.0, -1.0, 0.0);
    const auto n = make_vector(0.0, 1.0, 0.0);
    const auto r = v.reflect(n);
    EXPECT_EQ(r, make_vector(1.0, 1.0, 0.0));
}

TEST(Sphere, ReflectingSlanted) {
    const auto v = make_vector(0.0, -1.0, 0.0);
    const double loc = std::sqrt(2.0) / 2.0;
    const auto n = make_vector(loc, loc, 0.0);
    const auto r = v.reflect(n);
    EXPECT_EQ(r, make_vector(1.0, 0.0, 0.0));
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

TEST(Sphere, ConvertingPointToWorldSpaceToObjectSpace) {
    auto g1 = Group::make_group();
    g1->set_transform(tf::rotation_y(std::numbers::pi / 2));
    auto g2 = Group::make_group();
    g2->set_transform(tf::scaling(2.0, 2.0, 2.0));
    g1->add_child(g2);

    auto s = std::make_shared<Sphere>(Sphere{});
    s->set_transform(tf::translation(5.0, 0.0, 0.0));
    g2->add_child(s);

    EXPECT_EQ(s->world_to_object(make_point(-2.0, 0.0, -10.0)), make_point(0.0, 0.0, -1.0));
}

TEST(Sphere, ConvertingNormalFromObjectSpaceToWorldSpace) {
    auto g1 = Group::make_group();
    g1->set_transform(tf::rotation_y(std::numbers::pi / 2));
    auto g2 = Group::make_group();
    g2->set_transform(tf::scaling(1.0, 2.0, 3.0));
    g1->add_child(g2);

    auto s = std::make_shared<Sphere>(Sphere{});
    s->set_transform(tf::translation(5.0, 0.0, 0.0));
    g2->add_child(s);

    const auto loc = std::sqrt(3.0) / 3.0;
    EXPECT_EQ(s->normal_to_world(make_vector(loc, loc, loc)), make_vector(0.2857, 0.4286, -0.8571));
}
