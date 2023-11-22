#include <gtest/gtest.h>

#include "Sphere.h"
#include "Matrix.h"

TEST(Sphere, SphereDefaultTranformation) {
    const auto s = Sphere{};
    const auto expected_transform = Matrix<4, 4>::identity();
    EXPECT_EQ(s.transform(), expected_transform);
}