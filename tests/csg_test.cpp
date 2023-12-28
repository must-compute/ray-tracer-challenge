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

TEST(CSG, EvaluatingRuleForCSGOperation) {
  const std::vector<std::tuple<CSGOperation, bool, bool, bool, bool>> test_table = {
      // Union
      {CSGOperation::Union, true, true, true, false},
      {CSGOperation::Union, true, true, false, true},
      {CSGOperation::Union, true, false, true, false},
      {CSGOperation::Union, true, false, false, true},
      {CSGOperation::Union, false, true, true, false},
      {CSGOperation::Union, false, true, false, false},
      {CSGOperation::Union, false, false, true, true},
      {CSGOperation::Union, false, false, false, true},
      // Intersection
      {CSGOperation::Intersection, true, true, true, true},
      {CSGOperation::Intersection, true, true, false, false},
      {CSGOperation::Intersection, true, false, true, true},
      {CSGOperation::Intersection, true, false, false, false},
      {CSGOperation::Intersection, false, true, true, true},
      {CSGOperation::Intersection, false, true, false, true},
      {CSGOperation::Intersection, false, false, true, false},
      {CSGOperation::Intersection, false, false, false, false},
      // Difference
      {CSGOperation::Difference, true, true, true, false},
      {CSGOperation::Difference, true, true, false, true},
      {CSGOperation::Difference, true, false, true, false},
      {CSGOperation::Difference, true, false, false, true},
      {CSGOperation::Difference, false, true, true, true},
      {CSGOperation::Difference, false, true, false, true},
      {CSGOperation::Difference, false, false, true, false},
      {CSGOperation::Difference, false, false, false, false},

  };

  for (const auto &[op, left_hit, inside_left, inside_right, result] : test_table) {
    EXPECT_EQ(CSG::intersection_allowed(op, left_hit, inside_left, inside_right), result);
  }
}