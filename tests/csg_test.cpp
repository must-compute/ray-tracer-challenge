#include <gtest/gtest.h>

#include "CSG.h"
#include "Cube.h"
#include "Sphere.h"

TEST(CSG, CSGCreatedWithAnOperationAndTwoShapes) {
    const auto sphere{std::make_shared<Sphere>(Sphere{})};
    const auto cube{std::make_shared<Cube>(Cube{})};

    const auto csg{CSG::make_csg(CSGOperation::Union, sphere, cube)};
    EXPECT_EQ(csg->operation(), CSGOperation::Union);
    EXPECT_EQ(csg->left(), sphere);
    EXPECT_EQ(csg->right(), cube);
    EXPECT_EQ(sphere->parent(), csg);
    EXPECT_EQ(cube->parent(), csg);
}
