#include <gtest/gtest.h>

#include <numbers>
#include <cstddef>

#include "../src/Transformations.h"
#include "../src/Camera.h"
#include "../src/util.h"
#include "../src/World.h"

TEST(Camera, Constructor) {
  constexpr size_t hsize = 160;
  constexpr size_t vsize = 120;
  const double field_of_view = std::numbers::pi / 2.0;
  const auto c = Camera<hsize, vsize>(field_of_view);

  EXPECT_EQ(c.hsize(), hsize);
  EXPECT_EQ(c.vsize(), vsize);
  EXPECT_EQ(c.field_of_view(), field_of_view);
  EXPECT_EQ(c.transform(), tf::Transform::identity());
}

TEST(Camera, ConstructorPixelSize) {
  // Horizontal canvas
  {
    const size_t hsize = 200;
    const size_t vsize = 125;
    const double field_of_view = std::numbers::pi / 2.0;
    const auto c = Camera<hsize, vsize>(field_of_view);
    EXPECT_TRUE(within_epsilon(c.pixel_size(), 0.01));
  }

  // Vertical canvas
  {
    const size_t hsize = 125;
    const size_t vsize = 200;
    const double field_of_view = std::numbers::pi / 2.0;
    const auto c = Camera<hsize, vsize>(field_of_view);
    EXPECT_TRUE(within_epsilon(c.pixel_size(), 0.01));
  }
}

TEST(Camera, ConstructingRayThroughCenterOfCanvas) {
  const auto camera = Camera<201, 101>(std::numbers::pi / 2.0);
  const auto ray = camera.ray_for_pixel(100, 50);
  EXPECT_EQ(ray.origin(), Point(0.0, 0.0, 0.0));
  EXPECT_EQ(ray.direction(), Vector(0.0, 0.0, -1.0));
}

TEST(Camera, ConstructingRayThroughCornerOfCanvas) {
  const auto camera = Camera<201, 101>(std::numbers::pi / 2.0);
  const auto ray = camera.ray_for_pixel(0, 0);
  EXPECT_EQ(ray.origin(), Point(0.0, 0.0, 0.0));
  EXPECT_EQ(ray.direction(), Vector(0.66519, 0.33259, -0.66851));
}

TEST(Camera, ConstructingRayWhenCameraIsTransformed) {
  auto camera = Camera<201, 101>(std::numbers::pi / 2.0);
  camera.set_transform(tf::rotation_y(std::numbers::pi / 4.0) * tf::translation(0.0, -2.0, 5.0));
  const auto ray = camera.ray_for_pixel(100, 50);
  EXPECT_EQ(ray.origin(), Point(0.0, 2.0, -5.0));
  const auto loc = std::sqrt(2.0) / 2.0;
  EXPECT_EQ(ray.direction(), Vector(loc, 0.0, -loc));
}

TEST(Camera, RenderingWorldWithCamera) {
  const auto world = make_default_world();
  auto camera = Camera<11, 11>(std::numbers::pi / 2.0);

  const auto from = Point(0.0, 0.0, -5.0);
  const auto to = Point(0.0, 0.0, 0.0);
  const auto up = Vector(0.0, 1.0, 0.0);

  camera.set_transform(tf::view_transform(from, to, up));
  const auto image = camera.render(world);

  EXPECT_EQ(image.pixel_at(5, 5), (Color{0.38066, 0.47583, 0.2855}));
}



