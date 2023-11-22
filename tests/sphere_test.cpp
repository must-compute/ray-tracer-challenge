#include <gtest/gtest.h>

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
