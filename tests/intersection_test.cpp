#include <gtest/gtest.h>
#include <optional>
#include <memory>

#include "Intersection.h"
#include "Ray.h"
#include "Sphere.h"
#include "Plane.h"

TEST(Intersection, Creation) {
    const auto sphere = std::make_shared<Sphere>(Sphere{});
    const auto intersection = Intersection{3.5, sphere};
    EXPECT_EQ(intersection.t, 3.5);
    EXPECT_TRUE(intersection.object);
    EXPECT_EQ(intersection.object, sphere);
}

TEST(Intersection, Aggregating) {
    const auto sphere = std::make_shared<Sphere>(Sphere{});
    const auto i1 = Intersection{1.0, sphere};
    const auto i2 = Intersection{2.0, sphere};
    const auto xs = Intersections{i1, i2};
    ASSERT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 1.0);
    EXPECT_EQ(xs[1].t, 2.0);
}

TEST(Intersection, HitNonNegative) {
    const auto sphere = std::make_shared<Sphere>(Sphere{});
    const auto i1 = Intersection{1.0, sphere};
    const auto i2 = Intersection{2.0, sphere};
    const auto xs = Intersections{i1, i2};
    const auto hit_maybe = hit(xs);
    EXPECT_TRUE(hit_maybe);
    EXPECT_EQ(*hit_maybe, i1);
}

TEST(Intersection, HitSomeNegative) {
    const auto sphere = std::make_shared<Sphere>(Sphere{});
    const auto i1 = Intersection{-1.0, sphere};
    const auto i2 = Intersection{1.0, sphere};
    const auto xs = Intersections{i2, i1};
    const auto hit_maybe = hit(xs);
    EXPECT_TRUE(hit_maybe);
    EXPECT_EQ(*hit_maybe, i2);
}

TEST(Intersection, HitAllNegative) {
    const auto sphere = std::make_shared<Sphere>(Sphere{});
    const auto i1 = Intersection{-2.0, sphere};
    const auto i2 = Intersection{-1.0, sphere};
    const auto xs = Intersections{i2, i1};
    const auto hit_maybe = hit(xs);
    EXPECT_FALSE(hit_maybe);
}

TEST(Intersection, HitLowestNonNegative) {
    const auto sphere = std::make_shared<Sphere>(Sphere{});
    const auto i1 = Intersection{5.0, sphere};
    const auto i2 = Intersection{7.0, sphere};
    const auto i3 = Intersection{-3.0, sphere};
    const auto i4 = Intersection{2.0, sphere};
    const auto xs = Intersections{i1, i2, i3, i4};
    const auto hit_maybe = hit(xs);
    EXPECT_TRUE(hit_maybe);
    EXPECT_EQ(*hit_maybe, i4);
}

TEST(Intersection, PrecomputingIntersectionState) {
    const auto r = Ray{make_point(0.0, 0.0, -5.0), make_vector(0.0, 0.0, 1.0)};
    const auto sphere = std::make_shared<Sphere>(Sphere{});
    const auto i = Intersection{4.0, sphere};
    const auto comps = i.prepare_computations(r);
    EXPECT_EQ(comps.t, i.t);
    EXPECT_EQ(comps.object, i.object);
    EXPECT_EQ(comps.point, make_point(0.0, 0.0, -1.0));
    EXPECT_EQ(comps.eyev, make_vector(0.0, 0.0, -1.0));
    EXPECT_EQ(comps.normalv, make_vector(0.0, 0.0, -1.0));
}

TEST(Intersection, HitIntersectionOutside) {
    const auto r = Ray{make_point(0.0, 0.0, -5.0), make_vector(0.0, 0.0, 1.0)};
    const auto sphere = std::make_shared<Sphere>(Sphere{});
    const auto i = Intersection{4.0, sphere};
    const auto comps = i.prepare_computations(r);
    EXPECT_FALSE(comps.inside);
}

TEST(Intersection, HitIntersectionInside) {
    const auto r = Ray{make_point(0.0, 0.0, 0.0), make_vector(0.0, 0.0, 1.0)};
    const auto sphere = std::make_shared<Sphere>(Sphere{});
    const auto i = Intersection{1.0, sphere};
    const auto comps = i.prepare_computations(r);
    EXPECT_EQ(comps.point, make_point(0.0, 0.0, 1.0));
    EXPECT_EQ(comps.eyev, make_vector(0.0, 0.0, -1.0));
    EXPECT_EQ(comps.normalv, make_vector(0.0, 0.0, -1.0));
    EXPECT_TRUE(comps.inside);
}

TEST(Intersection, HitShouldOffsetPoint) {
    const auto r = Ray{make_point(0.0, 0.0, -5.0), make_vector(0.0, 0.0, 1.0)};
    auto sphere = std::make_shared<Sphere>(Sphere{});
    sphere->set_transform(tf::translation(0.0, 0.0, 1.0));
    const auto i = Intersection{5.0, sphere};
    const auto comps = i.prepare_computations(r);
    EXPECT_LT(comps.over_point.z(), -EPSILON / 2.0);
    EXPECT_GT(comps.point.z(), comps.over_point.z());
}

TEST(Intersection, PrecomputingTheReflectionVector) {
    const auto plane = std::make_shared<Plane>(Plane{});

    const auto loc = std::sqrt(2.0) / 2.0;
    const auto r = Ray{make_point(0.0, 1.0, -1.0), make_vector(0.0, -loc, loc)};

    const auto i = Intersection{std::sqrt(2.0), plane};

    const auto comps = i.prepare_computations(r);
    EXPECT_EQ(comps.reflectv, make_vector(0.0, loc, loc));
}
