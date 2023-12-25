#include <gtest/gtest.h>
#include <numbers>

#include "TestShape.h"
#include "Material.h"
#include "Matrix.h"
#include "Transformations.h"

TEST(TestShape, DefaultTransform) {
    const auto s = TestShape{};
    EXPECT_EQ(s.transform(), tf::Transform::identity());
}

TEST(TestShape, AssigningTransform) {
    auto s = TestShape{};
    const auto t = tf::translation(2.0, 3.0, 4.0);
    s.set_transform(t);
    EXPECT_EQ(s.transform(), t);
}

TEST(TestShape, DefaultMaterial) {
    auto s = TestShape{};
    EXPECT_EQ(s.material(), Material{});
}

TEST(TestShape, AssigningMaterial) {
    auto s = TestShape{};
    auto m = Material{};
    m.ambient = 1.0;
    s.set_material(m);
    EXPECT_EQ(s.material(), m);
}

TEST(TestShape, IntersectingScaledShapeWithRay) {
    const auto ray = Ray(make_point(0.0, 0.0, -5.0), make_vector(0.0, 0.0, 1.0));
    auto test_shape = TestShape{};
    test_shape.set_transform(tf::scaling(2.0, 2.0, 2.0));
    const auto xs = test_shape.intersect(ray);
    ASSERT_TRUE(test_shape.local_ray());
    EXPECT_EQ(test_shape.local_ray()->origin(), make_point(0.0, 0.0, -2.5));
    EXPECT_EQ(test_shape.local_ray()->direction(), make_vector(0.0, 0.0, 0.5));
}

TEST(TestShape, IntersectingTranslatedShapeWithRay) {
    const auto ray = Ray(make_point(0.0, 0.0, -5.0), make_vector(0.0, 0.0, 1.0));
    auto test_shape = TestShape{};
    test_shape.set_transform(tf::translation(5.0, 0.0, 0.0));
    const auto xs = test_shape.intersect(ray);
    ASSERT_TRUE(test_shape.local_ray());
    EXPECT_EQ(test_shape.local_ray()->origin(), make_point(-5.0, 0.0, -5.0));
    EXPECT_EQ(test_shape.local_ray()->direction(), make_vector(0.0, 0.0, 1.0));
}

TEST(TestShape, ComputingNormalOnATranslatedShape) {
    auto test_shape = TestShape{};
    test_shape.set_transform(tf::translation(0.0, 1.0, 0.0));
    EXPECT_EQ(test_shape.normal_at(make_point(0.0, 1.70711, -0.70711)), make_vector(0.0, 0.70711, -0.70711));
}

TEST(TestShape, ComputingNormalOnTransformedShape) {
    auto test_shape = TestShape{};
    test_shape.set_transform(tf::scaling(1.0, 0.5, 1.0) * tf::rotation_z(std::numbers::pi / 5.0));
    const double loc = std::sqrt(2.0) / 2.0;
    EXPECT_EQ(test_shape.normal_at(make_point(0.0, loc, -loc)), make_vector(0.0, 0.97014, -0.24254));
}

TEST(TestShape, ShapeHasParentAttribute) {
    const auto s = TestShape{};
    EXPECT_EQ(s.parent(), nullptr);
}