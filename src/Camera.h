#ifndef RAY_TRACER_CHALLENGE_CAMERA_H
#define RAY_TRACER_CHALLENGE_CAMERA_H

#include <cstddef>
#include <thread>
#include <vector>
#include "Canvas.h"
#include "Ray.h"
#include "Transformations.h"
#include "World.h"

template<size_t WIDTH, size_t HEIGHT>
class Camera {

public:
  explicit Camera(const double field_of_view_in) :
      field_of_view_(field_of_view_in),
      transform_(tf::Transform::identity()) {
    // Calculate the pixel_size_, half_width_, and half_height_ given the field of view and h/v size.
    const double half_view = std::tan(field_of_view_ / 2.0);
    const auto aspect_ratio = static_cast<double>(WIDTH) / static_cast<double>(HEIGHT);
    if (aspect_ratio >= 1.0) {
      half_width_ = half_view;
      half_height_ = half_view / aspect_ratio;
    } else {
      half_width_ = half_view * aspect_ratio;
      half_height_ = half_view;
    }
    pixel_size_ = (half_width_ * 2.0) / static_cast<double>(WIDTH);
  }

  [[nodiscard]] size_t hsize() const {
    return WIDTH;
  }

  [[nodiscard]] size_t vsize() const {
    return HEIGHT;
  }

  [[nodiscard]] double field_of_view() const {
    return field_of_view_;
  }

  [[nodiscard]] const tf::Transform &transform() const {
    return transform_;
  }

  void set_transform(const tf::Transform &t) {
    transform_ = t;
  }

  [[nodiscard]]     double pixel_size() const {
    return pixel_size_;
  }

  void set_pixel_size(double pixel_size_in) {
    pixel_size_ = pixel_size_in;
  }

  [[nodiscard]] Ray ray_for_pixel(size_t pixel_x, size_t pixel_y) const {
    // the offset from canvas edge to the pixel's center
    const auto x_offset = (static_cast<double>(pixel_x) + 0.5) * pixel_size_;
    const auto y_offset = (static_cast<double>(pixel_y) + 0.5) * pixel_size_;

    // the untransformed coordinates of the pixel in world space
    const auto world_x = half_width_ - x_offset;
    const auto world_y = half_height_ - y_offset;

    const auto pixel = transform_.inverse() * make_point(world_x, world_y, -1);
    const auto origin = transform_.inverse() * make_point(0.0, 0.0, 0.0);
    const auto direction = (pixel - origin).normalize();

    return {origin, direction};
  }

  [[nodiscard]] Canvas<WIDTH, HEIGHT> render(const World &world) const {
    auto image = Canvas<WIDTH, HEIGHT>{};
    std::vector<std::thread> threads;

    for (size_t y = 0; y < HEIGHT; ++y) {
      threads.emplace_back([&, y] {
        for (size_t x = 0; x < WIDTH; ++x) {
          const auto ray = ray_for_pixel(x, y);
          const auto color = world.color_at(ray);
          image.write_pixel(x, y, color);
        }
      });
    }

    for (auto &thread : threads) {
      thread.join();
    }

    return image;
  }

private:
  double field_of_view_;
  tf::Transform transform_;
  // The size of each pixel in world units.
  double pixel_size_;
  // The size of half the canvas width in world units.
  double half_width_;
  // The size of half the canvas height in world units.
  double half_height_;
};

#endif //RAY_TRACER_CHALLENGE_CAMERA_H