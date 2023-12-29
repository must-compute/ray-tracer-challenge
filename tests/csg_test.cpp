#include <gtest/gtest.h>

#include "CSG.h"
#include "Cube.h"
#include "Sphere.h"
#include "TestShape.h"

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

TEST(CSG, FilteringListOfIntersections) {
  const std::vector<std::tuple<CSGOperation, size_t, size_t>> test_table = {
      {CSGOperation::Union, 0, 3},
      {CSGOperation::Intersection, 1, 2},
      {CSGOperation::Difference, 0, 1},
  };

  auto sphere{std::make_shared<Sphere>(Sphere{})};
  auto cube{std::make_shared<Cube>(Cube{})};

  for (const auto &[op, x0, x1] : test_table) {
    const auto csg{CSG::make_csg(op, sphere, cube)};
    const Intersections xs{
        Intersection{1.0, sphere.get()},
        Intersection{2.0, cube.get()},
        Intersection{3.0, sphere.get()},
        Intersection{4.0, cube.get()},
    };
    const auto result = csg->filter_intersections(xs);
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], xs[x0]);
    EXPECT_EQ(result[1], xs[x1]);
  }
}

TEST(CSG, RayMissesCSGObject) {
  auto sphere{std::make_shared<Sphere>(Sphere{})};
  auto cube{std::make_shared<Cube>(Cube{})};
  const auto csg{CSG::make_csg(CSGOperation::Union, sphere, cube)};
  const auto ray{Ray{make_point(0.0, 2.0, -5.0), make_vector(0.0, 0.0, 1.0)}};
  EXPECT_TRUE(csg->local_intersect(ray).empty());
}

TEST(CSG, RayHitsCSGObject) {
  auto sphere1{std::make_shared<Sphere>(Sphere{})};
  auto sphere2{std::make_shared<Sphere>(Sphere{})};
  sphere2->set_transform(tf::translation(0.0, 0.0, 0.5));

  const auto csg{CSG::make_csg(CSGOperation::Union, sphere1, sphere2)};
  const auto ray{Ray{make_point(0.0, 0.0, -5.0), make_vector(0.0, 0.0, 1.0)}};
  const auto xs = csg->local_intersect(ray);

  ASSERT_EQ(xs.size(), 2);
  EXPECT_EQ(xs[0].t, 4.0);
  EXPECT_EQ(xs[0].object, sphere1.get());
  EXPECT_EQ(xs[1].t, 6.5);
  EXPECT_EQ(xs[1].object, sphere2.get());
}

TEST(CSG, CSGHasBoundingBoxThatContainsItsChildren) {
  auto left{std::make_shared<Sphere>(Sphere{})};
  auto right{std::make_shared<Sphere>(Sphere{})};
  right->set_transform(tf::translation(2.0, 3.0, 4.0));

  const auto csg = CSG::make_csg(CSGOperation::Difference, left, right);
  const auto box = csg->make_bounding_box();
  EXPECT_EQ(box.minimum(), make_point(-1.0, -1.0, -1.0));
  EXPECT_EQ(box.maximum(), make_point(3.0, 4.0, 5.0));
}

TEST(CSG, RayDoesNotIntersectChildrenIfBoundingBoxIsMissed) {
  const auto left = std::make_shared<TestShape>(TestShape{});
  const auto right = std::make_shared<TestShape>(TestShape{});
  const auto csg = CSG::make_csg(CSGOperation::Difference, left, right);
  const auto ray = Ray{make_point(0.0, 0.0, -5.0), make_vector(0.0, 1.0, 0.0)};
  auto xs = csg->intersect(ray);
  EXPECT_FALSE(left->local_ray());
  EXPECT_FALSE(right->local_ray());
}

TEST(CSG, RayIntersectsChildrenIfBoundingBoxIsHit) {
  const auto left = std::make_shared<TestShape>(TestShape{});
  const auto right = std::make_shared<TestShape>(TestShape{});
  const auto csg = CSG::make_csg(CSGOperation::Difference, left, right);
  const auto ray = Ray{make_point(0.0, 0.0, -5.0), make_vector(0.0, 0.0, 1.0)};
  auto xs = csg->intersect(ray);
  EXPECT_TRUE(left->local_ray());
  EXPECT_TRUE(right->local_ray());
}