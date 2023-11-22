#include <gtest/gtest.h>

#include "Intersection.h"
#include "Sphere.h"
#include <optional>

TEST(Intersection, Creation) {
    const auto sphere = Sphere();
    const auto intersection = Intersection{3.5, sphere};
    EXPECT_EQ(intersection.t, 3.5);
    EXPECT_EQ(intersection.object, sphere);
}

TEST(Intersection, Aggregating) {
    const auto sphere = Sphere();
    const auto i1 = Intersection{1.0, sphere};
    const auto i2 = Intersection{2.0, sphere};
    const auto xs = Intersections{i1, i2};
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 1.0);
    EXPECT_EQ(xs[1].t, 2.0);
}

TEST(Intersection, HitNonNegative) {
    const auto s = Sphere();
    const auto i1 = Intersection{1.0, s};
    const auto i2 = Intersection{2.0, s};
    const auto xs = Intersections{i1, i2};
    const auto hit_maybe = hit(xs);
    EXPECT_TRUE(hit_maybe);
    EXPECT_EQ(*hit_maybe, i1);
}

TEST(Intersection, HitSomeNegative) {
    const auto s = Sphere();
    const auto i1 = Intersection{-1.0, s};
    const auto i2 = Intersection{1.0, s};
    const auto xs = Intersections{i2, i1};
    const auto hit_maybe = hit(xs);
    EXPECT_TRUE(hit_maybe);
    EXPECT_EQ(*hit_maybe, i2);
}

TEST(Intersection, HitAllNegative) {
    const auto s = Sphere();
    const auto i1 = Intersection{-2.0, s};
    const auto i2 = Intersection{-1.0, s};
    const auto xs = Intersections{i2, i1};
    const auto hit_maybe = hit(xs);
    EXPECT_FALSE(hit_maybe);
}

TEST(Intersection, HitLowestNonNegative) {
    const auto s = Sphere();
    const auto i1 = Intersection{5.0, s};
    const auto i2 = Intersection{7.0, s};
    const auto i3 = Intersection{-3.0, s};
    const auto i4 = Intersection{2.0, s};
    const auto xs = Intersections{i1, i2, i3, i4};
    const auto hit_maybe = hit(xs);
    EXPECT_TRUE(hit_maybe);
    EXPECT_EQ(*hit_maybe, i4);
}
