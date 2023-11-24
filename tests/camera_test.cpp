#include <gtest/gtest.h>

#include <numbers>
#include <cmath>
#include <cstddef>

#include "../src/Transformations.h"
#include "../src/Camera.h"
#include "../src/util.h"

TEST(Camera, Constructor) {
    const size_t hsize = 160;
    const size_t vsize = 120;
    const double field_of_view = std::numbers::pi / 2.0;
    const auto c = Camera(hsize, vsize, field_of_view);

    EXPECT_EQ(c.get_hsize(), hsize);
    EXPECT_EQ(c.get_vsize(), vsize);
    EXPECT_EQ(c.get_field_of_view(), field_of_view);
    EXPECT_EQ(c.get_transform(), tf::Transform::identity());
}

TEST(Camera, ConstructorPixelSize) {
    // Horizontal canvas
    {
        const size_t hsize = 200;
        const size_t vsize = 125;
        const double field_of_view = std::numbers::pi / 2.0;
        const auto c = Camera(hsize, vsize, field_of_view);
        EXPECT_TRUE(within_epsilon(c.get_pixel_size(), 0.01));
    }

    // Vertical canvas
    {
        const size_t hsize = 125;
        const size_t vsize = 200;
        const double field_of_view = std::numbers::pi / 2.0;
        const auto c = Camera(hsize, vsize, field_of_view);
        EXPECT_TRUE(within_epsilon(c.get_pixel_size(), 0.01));
    }
}
