#include <filesystem>
#include "Canvas.h"
#include "Sphere.h"
#include "Ray.h"

int main() {
    constexpr size_t width = 100;
    constexpr size_t height = width;
    const auto ray_origin = make_point(0.0, 0.0, -5.0);
    const auto wall_z = 10.0;
    const auto wall_size = 7.0;
    const auto pixel_size = wall_size / width;
    const Color white = make_color(1.0, 1.0, 1.0);
    const Color black = make_color(0.0, 0.0, 0.0);
    auto s = Sphere{};
    auto canvas = Canvas<width, height>();

    for (size_t row = 0; row < height; ++row) {
        const auto world_y = (wall_size / 2.0) - (pixel_size * static_cast<double>(row));
        for (size_t col = 0; col < width; ++col) {
            const auto world_x = (wall_size / 2.0) - (pixel_size * static_cast<double>(col));
            const auto position = make_point(world_x, world_y, wall_z);
            const auto ray = Ray(ray_origin, (position - ray_origin).normalize());
            const auto xs = ray.intersect(s);
            const auto selected_color = xs.empty() ? white : black;
            canvas.write_pixel(col, row, selected_color);
        }
    }
    std::filesystem::path temp_path = "./output.ppm";
    canvas.to_file(temp_path);
    return 0;
}
