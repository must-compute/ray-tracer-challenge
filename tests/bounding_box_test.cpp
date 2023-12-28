#include <gtest/gtest.h>

#include <numbers>

#include "BoundingBox.h"
#include "Sphere.h"
#include "Transformations.h"
#include "Cylinder.h"
#include "Group.h"

TEST(BoundingBox, AddPoint) {
  auto box1 = BoundingBox{make_point(-1.0, -1.0, -1.0), make_point(1.0, 1.0, 1.0)};
  box1.add_point(make_point(-1000.0, 0.0, 0.0));
  EXPECT_EQ(box1.minimum(), make_point(-1000.0, -1.0, -1.0));
  EXPECT_EQ(box1.maximum(), make_point(1.0, 1.0, 1.0));
}

TEST(BoundingBox, AddingOneBoundingBoxToAnother) {
  auto box1 = BoundingBox{make_point(-5.0, -2.0, 0.0), make_point(7.0, 4.0, 4.0)};
  const auto box2 = BoundingBox{make_point(8.0, -7.0, -2.0), make_point(14.0, 2.0, 8.0)};
  box1.add_box(box2);
  EXPECT_EQ(box1.minimum(), make_point(-5.0, -7.0, -2.0));
  EXPECT_EQ(box1.maximum(), make_point(14.0, 4.0, 8.0));
}

TEST(BoundingBox, BoxContainsGivenPoint) {
  const auto box = BoundingBox{make_point(5.0, -2.0, 0.0), make_point(11.0, 4.0, 7.0)};
  const std::vector<std::tuple<Tuple, bool>> table = {
      {make_point(5.0, -2.0, 0.0), true},
      {make_point(11.0, 4.0, 7.0), true},
      {make_point(8.0, 1.0, 3.0), true},
      {make_point(3.0, 0.0, 3.0), false},
      {make_point(8.0, -4.0, 3.0), false},
      {make_point(8.0, 1.0, -1.0), false},
      {make_point(13.0, 1.0, 3.0), false},
      {make_point(8.0, 5.0, 3.0), false},
      {make_point(8.0, 1.0, 8.0), false}
  };

  for (const auto &[point, result] : table) {
    EXPECT_EQ(box.contains_point(point), result);
  }
}

TEST(BoundingBox, BoxContainsAnotherBox) {
  const auto box1 = BoundingBox{make_point(5.0, -2.0, 0.0), make_point(11.0, 4.0, 7.0)};
  const std::vector<std::tuple<Tuple, Tuple, bool>> table = {
      {make_point(5.0, -2.0, 0.0), make_point(11.0, 4.0, 7.0), true},
      {make_point(6.0, -1.0, 1.0), make_point(10.0, 3.0, 6.0), true},
      {make_point(4.0, -3.0, -1.0), make_point(10.0, 3.0, 6.0), false},
      {make_point(6.0, -1.0, 1.0), make_point(12.0, 5.0, 8.0), false}
  };

  for (const auto &[min, max, result] : table) {
    const auto box2 = BoundingBox{min, max};
    EXPECT_EQ(box1.contains_box(box2), result);
  }
}

TEST(BoundingBox, TransformingBoundingBox) {
  auto box = BoundingBox{make_point(-1.0, -1.0, -1.0), make_point(1.0, 1.0, 1.0)};
  box.set_transform(tf::rotation_x(std::numbers::pi / 4.0) * tf::rotation_y(std::numbers::pi / 4.0));
  EXPECT_EQ(box.minimum(), make_point(-1.4142, -1.7071, -1.7071));
  EXPECT_EQ(box.maximum(), make_point(1.4142, 1.7071, 1.7071));
}

TEST(BoundingBox, QueryingSphereBoundingBoxInItsParentSpace) {
  auto sphere = std::make_shared<Sphere>(Sphere{});
  sphere->set_transform(tf::translation(1.0, -3.0, 5.0) * tf::scaling(0.5, 2.0, 4.0));
  const auto box = sphere->make_bounding_box_in_parent_space();
  EXPECT_EQ(box.minimum(), make_point(0.5, -5.0, 1.0));
  EXPECT_EQ(box.maximum(), make_point(1.5, -1.0, 9.0));
}

TEST(BoundingBox, GroupHasBoundingBoxContainingChildren) {
  auto sphere = std::make_shared<Sphere>(Sphere{});
  sphere->set_transform(tf::translation(2.0, 5.0, -3.0) * tf::scaling(2.0, 2.0, 2.0));

  auto cylinder = std::make_shared<Cylinder>(Cylinder{});
  cylinder->set_minimum(-2.0);
  cylinder->set_maximum(2.0);
  cylinder->set_transform(tf::translation(-4.0, -1.0, 4.0) * tf::scaling(0.5, 1.0, 0.5));

  auto group = Group::make_group();
  group->add_child(sphere);
  group->add_child(cylinder);

  const auto box = group->make_bounding_box();
  EXPECT_EQ(box.minimum(), make_point(-4.5, -3.0, -5.0));
  EXPECT_EQ(box.maximum(), make_point(4.0, 7.0, 4.5));
}

TEST(BoundingBox, IntersectingRayWithBoundingBoxAtOrigin) {
  const auto box = BoundingBox{make_point(-1.0, -1.0, -1.0), make_point(1.0, 1.0, 1.0)};
  const std::vector<std::tuple<Tuple, Tuple, bool>> table = {
      {make_point(5.0, 0.5, 0.0), make_vector(-1.0, 0.0, 0.0), true},
      {make_point(-5.0, 0.5, 0.0), make_vector(1.0, 0.0, 0.0), true},
      {make_point(0.5, 5.0, 0.0), make_vector(0.0, -1.0, 0.0), true},
      {make_point(0.5, -5.0, 0.0), make_vector(0.0, 1.0, 0.0), true},
      {make_point(0.5, 0.0, 5.0), make_vector(0.0, 0.0, -1.0), true},
      {make_point(0.5, 0.0, -5.0), make_vector(0.0, 0.0, 1.0), true},
      {make_point(0.0, 0.5, 0.0), make_vector(0.0, 0.0, 1.0), true},
      {make_point(-2.0, 0.0, 0.0), make_vector(2.0, 4.0, 6.0), false},
      {make_point(0.0, -2.0, 0.0), make_vector(6.0, 2.0, 4.0), false},
      {make_point(0.0, 0.0, -2.0), make_vector(4.0, 6.0, 2.0), false},
      {make_point(2.0, 0.0, 2.0), make_vector(0.0, 0.0, -1.0), false},
      {make_point(0.0, 2.0, 2.0), make_vector(0.0, -1.0, 0.0), false},
      {make_point(2.0, 2.0, 0.0), make_vector(-1.0, 0.0, 0.0), false},
  };
  for (const auto &[origin, direction, result] : table) {
    const auto ray = Ray{origin, direction.normalize()};
    EXPECT_EQ(box.intersects(ray), result);
  }
}

TEST(BoundingBox, IntersectingRayWithNonCubicBoundingBox) {
  const auto box = BoundingBox{make_point(5.0, -2.0, 0.0), make_point(11.0, 4.0, 7.0)};
  const std::vector<std::tuple<Tuple, Tuple, bool>> table = {
      {make_point(15.0, 1.0, 2.0), make_vector(-1.0, 0.0, 0.0), true},
      {make_point(-5.0, -1.0, 4.0), make_vector(1.0, 0.0, 0.0), true},
      {make_point(7.0, 6.0, 5.0), make_vector(0.0, -1.0, 0.0), true},
      {make_point(9.0, -5.0, 6.0), make_vector(0.0, 1.0, 0.0), true},
      {make_point(8.0, 2.0, 12.0), make_vector(0.0, 0.0, -1.0), true},
      {make_point(6.0, 0.0, -5.0), make_vector(0.0, 0.0, 1.0), true},
      {make_point(8.0, 1.0, 3.5), make_vector(0.0, 0.0, 1.0), true},
      {make_point(9.0, -1.0, -8.0), make_vector(2.0, 4.0, 6.0), false},
      {make_point(8.0, 3.0, -4.0), make_vector(6.0, 2.0, 4.0), false},
      {make_point(9.0, -1.0, -2.0), make_vector(4.0, 6.0, 2.0), false},
      {make_point(4.0, 0.0, 9.0), make_vector(0.0, 0.0, -1.0), false},
      {make_point(8.0, 6.0, -1.0), make_vector(0.0, -1.0, 0.0), false},
      {make_point(12.0, 5.0, 4.0), make_vector(-1.0, 0.0, 0.0), false},
  };
  for (const auto &[origin, direction, result] : table) {
    const auto ray = Ray{origin, direction.normalize()};
    EXPECT_EQ(box.intersects(ray), result);
  }
}