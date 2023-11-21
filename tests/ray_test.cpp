#include <gtest/gtest.h>

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
