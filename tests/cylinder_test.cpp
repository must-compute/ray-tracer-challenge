#include <gtest/gtest.h>

#include "Cylinder.h"
#include "Ray.h"
#include "Tuple.h"
#include "Transformations.h"

TEST(Cylinder, RayMissesCylinder) {
    const std::vector<std::tuple<Tuple, Tuple>> test_table = {
            {make_point(1.0, 0.0, 0.0),  make_vector(0.0, 1.0, 0.0)},
            {make_point(0.0, 0.0, 0.0),  make_vector(0.0, 1.0, 0.0)},
            {make_point(0.0, 0.0, -5.0), make_vector(1.0, 1.0, 0.0)},
    };

    for (const auto &[origin, direction]: test_table) {
        auto cylinder = Cylinder{};
        const auto ray = Ray{origin, direction.normalize()};
        const auto xs = cylinder.local_intersect(ray);
        ASSERT_EQ(xs.size(), 0);
    }
}

TEST(Cylinder, RayHitsCylinder) {
    const std::vector<std::tuple<Tuple, Tuple, double, double>> test_table = {
            {make_point(1.0, 0.0, -5.0), make_vector(0.0, 0.0, 1.0), 5.0,     5.0},
            {make_point(0.0, 0.0, -5.0), make_vector(0.0, 0.0, 1.0), 4.0,     6.0},
            {make_point(0.5, 0.0, -5.0), make_vector(0.1, 1.0, 1.0), 6.80798, 7.08872},
    };

    for (const auto &[origin, direction, t0, t1]: test_table) {
        auto cylinder = Cylinder{};
        const auto ray = Ray{origin, direction.normalize()};
        const auto xs = cylinder.local_intersect(ray);
        ASSERT_EQ(xs.size(), 2);
        EXPECT_TRUE(within_epsilon(xs[0].t, t0));
        EXPECT_TRUE(within_epsilon(xs[1].t, t1));
    }
}
