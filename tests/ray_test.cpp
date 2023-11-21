#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Ray.h"
#include "Sphere.h"
#include "Tuple.h"

TEST(Ray, Creation) {
    const auto origin = make_point(1.0, 2.0, 3.0);
    const auto direction = make_vector(4.0, 5.0, 6.0);
    const auto r = Ray(origin, direction);
    EXPECT_EQ(r.origin(), origin);
    EXPECT_EQ(r.direction(), direction);
}

TEST(Ray, PositionAtT) {
    const auto r = Ray(make_point(2.0, 3.0, 4.0), make_vector(1.0, 0.0, 0.0));
    EXPECT_EQ(r.position_at_t(0.0), make_point(2.0, 3.0, 4.0));
    EXPECT_EQ(r.position_at_t(1.0), make_point(3.0, 3.0, 4.0));
    EXPECT_EQ(r.position_at_t(-1.0), make_point(1.0, 3.0, 4.0));
    EXPECT_EQ(r.position_at_t(2.5), make_point(4.5, 3.0, 4.0));
}

TEST(Ray, IntersectSphereTwoPoints) {
    const auto r = Ray(make_point(0.0, 0.0, -5.0), make_vector(0.0, 0.0, 1.0));
    const auto s = Sphere{};
    const auto intersections = r.intersect(s);

    EXPECT_EQ(intersections.size(), 2);
    EXPECT_THAT(intersections, ::testing::ElementsAre(4.0, 6.0));
}

TEST(Ray, IntersectSphereTangent) {
    const auto r = Ray(make_point(0.0, 1.0, -5.0), make_vector(0.0, 0.0, 1.0));
    const auto s = Sphere{};
    const auto intersections = r.intersect(s);

    // Intentionally assert that a tangent intersection returns two identical values, as the book recommends to ease things for later chapters.
    EXPECT_EQ(intersections.size(), 2);
    EXPECT_THAT(intersections, ::testing::ElementsAre(5.0, 5.0));
}

TEST(Ray, IntersectSphereMiss) {
    const auto r = Ray(make_point(0.0, 2.0, -5.0), make_vector(0.0, 0.0, 1.0));
    const auto s = Sphere{};
    const auto intersections = r.intersect(s);
    EXPECT_EQ(intersections.size(), 0);
}

TEST(Ray, IntersectOriginatesInsideSphere) {
    const auto r = Ray(make_point(0.0, 0.0, 0.0), make_vector(0.0, 0.0, 1.0));
    const auto s = Sphere{};
    const auto intersections = r.intersect(s);
    EXPECT_EQ(intersections.size(), 2);
    EXPECT_THAT(intersections, ::testing::ElementsAre(-1.0, 1.0));
}

TEST(Ray, IntersectSphereBehindRay) {
    const auto r = Ray(make_point(0.0, 0.0, 5.0), make_vector(0.0, 0.0, 1.0));
    const auto s = Sphere{};
    const auto intersections = r.intersect(s);
    EXPECT_EQ(intersections.size(), 2);
    EXPECT_THAT(intersections, ::testing::ElementsAre(-6.0, -4.0));
}
