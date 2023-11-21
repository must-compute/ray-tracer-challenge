#include <gtest/gtest.h>

#include "Intersection.h"
#include "Sphere.h"

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