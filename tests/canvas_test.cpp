#include <gtest/gtest.h>

#include "../src/Canvas.h"
#include <filesystem>
#include <fstream>

TEST(Canvas, Basic) {
    {
        constexpr size_t width = 100;
        constexpr size_t height = 100;
        const Canvas<width, height> canvas;

        EXPECT_EQ(canvas.width(), width);
        EXPECT_EQ(canvas.height(), height);
        const Color black_pixel = make_color(0.0, 0.0, 0.0);
        for (const auto &row: canvas.pixels()) {
            for (const auto &pixel: row) {
                EXPECT_EQ(pixel, black_pixel);
            }
        }
    }
}

TEST(Canvas, WritePixel) {
    {
        constexpr size_t width = 100;
        constexpr size_t height = 100;
        Canvas<width, height> canvas;

        const Color red = make_color(1.0, 0.0, 0.0);
        canvas.write_pixel(2, 3, red);
        EXPECT_EQ(canvas.pixel_at(2, 3), red);
    }
}

TEST(Canvas, PPMHeaderConstruction) {
    constexpr size_t width = 100;
    constexpr size_t height = 200;
    const Canvas<width, height> canvas;

// Check that the PPM header is at the very beginning of the PPM string.
    const std::string expected = "P3\n100 200\n255\n";
    EXPECT_EQ(canvas.to_ppm().find(expected), 0);
}

TEST(Canvas, PPMPixelConstruction) {
    constexpr size_t width = 5;
    constexpr size_t height = 3;
    Canvas<width, height> canvas;

    const Color c1 = make_color(1.5, 0.0, 0.0);
    const Color c2 = make_color(0.0, 0.5, 0.0);
    const Color c3 = make_color(-0.5, 0.0, 1.0);
    canvas.write_pixel(0, 0, c1);
    canvas.write_pixel(2, 1, c2);
    canvas.write_pixel(4, 2, c3);
    const std::string expected_ppm_header = "P3\n5 3\n255\n";
    EXPECT_EQ(canvas.to_ppm().find(expected_ppm_header), 0);
    constexpr auto expected = R"(255 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 128 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 255
)";
    EXPECT_EQ(canvas.ppm_body(), expected);
    EXPECT_EQ(canvas.to_ppm().find(expected), expected_ppm_header.length());
}

TEST(Canvas, PPMSeventyCharLimit) {
    constexpr size_t width = 10;
    constexpr size_t height = 2;
    Canvas<width, height> canvas;

    const Color c = make_color(1, 0.8, 0.6);
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            canvas.write_pixel(x, y, c);
        }
    }
    constexpr auto expected = R"(255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204
153 255 204 153 255 204 153 255 204 153 255 204 153
255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204
153 255 204 153 255 204 153 255 204 153 255 204 153
)";
    EXPECT_EQ(canvas.ppm_body(), expected);
}

TEST(Canvas, PPMFileSaving) {
// CREATE CANVAS AND WRITE IT TO FILE
    constexpr size_t width = 5;
    constexpr size_t height = 3;
    Canvas<width, height> canvas;

    const Color c1 = make_color(1.5, 0.0, 0.0);
    const Color c2 = make_color(0.0, 0.5, 0.0);
    const Color c3 = make_color(-0.5, 0.0, 1.0);
    canvas.write_pixel(0, 0, c1);
    canvas.write_pixel(2, 1, c2);
    canvas.write_pixel(4, 2, c3);

    std::filesystem::path temp_path = std::filesystem::temp_directory_path() / "ray_tracer_test01.ppm";
    canvas.to_file(temp_path);

    std::ifstream infile(temp_path);
    std::stringstream ss;
    ss << infile.rdbuf();
    EXPECT_EQ(ss.str(), canvas.to_ppm());
    EXPECT_TRUE(std::filesystem::remove(temp_path));
}
