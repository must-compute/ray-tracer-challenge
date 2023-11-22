#include <gtest/gtest.h>
#include <cmath>

#include "Sphere.h"
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

TEST(Sphere, ComputingNormalOnTranslatedSphere) {
    auto s = Sphere{};
    s.set_transform(tf::translation(0.0, 1.0, 0.0));
    const auto n = s.normal_at(make_point(0.0, 1.70711, -0.70711));
    EXPECT_EQ(n, make_vector(0, 0.70711, -0.70711));
}

TEST(Sphere, ComputingNormalOnTransformedSphere) {
    auto s = Sphere{};
    const auto m = tf::scaling(1.0, 0.5, 1.0) * tf::rotation_z(M_PI / 5.0);
    s.set_transform(m);
    const auto n = s.normal_at(make_point(0.0, std::sqrt(2.0) / 2.0, -std::sqrt(2.0) / 2.0));
    EXPECT_EQ(n, make_vector(0, 0.97014, -0.24254));
}
