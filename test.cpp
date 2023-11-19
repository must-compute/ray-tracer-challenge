#include <gtest/gtest.h>

#include <map>
#include "Tuple.h"
#include "Matrix.h"
#include "Color.h"
#include "Canvas.h"
#include <filesystem>
#include <fstream>


class RayTracerFixture : public ::testing::Test {
protected:

    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(RayTracerFixture, PlaceholderTest) {
    EXPECT_EQ(1 + 1, 2);
}

// TODO do we have EXPECT WITHIN EPSILON

TEST_F(RayTracerFixture, TupleBasic) {
    double x, y, z, w;
    x = 1.0;
    y = 2.2;
    z = 3.5;
    w = 1.0;
    const Tuple t = Tuple(x, y, z, w);
    EXPECT_EQ(t.x(), x);
    EXPECT_EQ(t.y(), y);
    EXPECT_EQ(t.z(), z);
    EXPECT_EQ(t.w(), w);
    EXPECT_TRUE(t.is_point());
    EXPECT_FALSE(t.is_vector());
}

TEST_F(RayTracerFixture, TupleFactoryTest) {
    double x = 1.0;
    double y = 2.2;
    double z = 3.5;
    const Tuple point_tuple = make_point(x, y, z);
    const Tuple t1 = Tuple(x, y, z, 1.0);
    EXPECT_EQ(point_tuple, t1);

    const Tuple vector_tuple = make_vector(x, y, z);
    const Tuple t2 = Tuple(x, y, z, 0.0);
    EXPECT_EQ(vector_tuple, t2);
}

TEST_F(RayTracerFixture, TupleAddition) {
    const Tuple t1 = Tuple(3.0, -2.0, 5.0, 1.0);
    const Tuple t2 = Tuple(-2.0, 3.0, 1.0, 0.0);

    EXPECT_EQ(t1 + t2, Tuple(1.0, 1.0, 6.0, 1.0));
}

TEST_F(RayTracerFixture, TupleSubtraction) {
    {
        const Tuple p1 = make_point(3.0, 2.0, 1.0);
        const Tuple p2 = make_point(5.0, 6.0, 7.0);
        EXPECT_EQ(p1 - p2, make_vector(-2.0, -4.0, -6.0));
    }
    {
        const Tuple p1 = make_point(3.0, 2.0, 1.0);
        const Tuple v1 = make_vector(5.0, 6.0, 7.0);
        EXPECT_EQ(p1 - v1, make_point(-2.0, -4.0, -6.0));
    }
    {
        const Tuple v1 = make_vector(3.0, 2.0, 1.0);
        const Tuple v2 = make_vector(5.0, 6.0, 7.0);
        EXPECT_EQ(v1 - v2, make_vector(-2.0, -4.0, -6.0));
    }
    {
        const Tuple v1 = make_vector(0.0, 0.0, 0.0);
        const Tuple v2 = make_vector(5.0, 6.0, 7.0);
        EXPECT_EQ(v1 - v2, make_vector(-5.0, -6.0, -7.0));
    }
}

TEST_F(RayTracerFixture, TupleNegation) {
    {
        const Tuple t1 = make_vector(1.0, 2.0, 3.0);
        EXPECT_EQ(-t1, make_vector(-1.0, -2.0, -3.0));
    }
    {
        const Tuple t1 = make_point(1.0, 2.0, 3.0);
        EXPECT_NE(-t1, make_point(-1.0, -2.0, -3.0));
    }
}


TEST_F(RayTracerFixture, TupleScalarMultiply) {
    {
        const Tuple t = Tuple(1.0, -2.0, 3.0, -4.0);
        EXPECT_EQ(t * 3.5, Tuple(3.5, -7.0, 10.5, -14.0));
    }
    {
        const Tuple t = Tuple(1.0, -2.0, 3.0, -4.0);
        EXPECT_EQ(t * 0.5, Tuple(0.5, -1.0, 1.5, -2.0));
    }
}

TEST_F(RayTracerFixture, TupleScalarDivide) {
    const Tuple t = Tuple(1.0, -2.0, 3.0, -4.0);
    EXPECT_EQ(t / 2.0, Tuple(0.5, -1.0, 1.5, -2.0));
}


TEST_F(RayTracerFixture, TupleMagnitude) {
    {
        const Tuple v = make_vector(1.0, 0.0, 0.0);
        EXPECT_EQ(v.magnitude(), 1.0);
    }
    {
        const Tuple v = make_vector(0.0, 1.0, 0.0);
        EXPECT_EQ(v.magnitude(), 1.0);
    }
    {
        const Tuple v = make_vector(0.0, 0.0, 1.0);
        EXPECT_EQ(v.magnitude(), 1.0);
    }
    {
        const Tuple v = make_vector(1.0, 2.0, 3.0);
        EXPECT_TRUE(within_epsilon(v.magnitude(), std::sqrt(14.0)));
    }
    {
        const Tuple v = make_vector(-1.0, -2.0, -3.0);
        EXPECT_TRUE(within_epsilon(v.magnitude(), std::sqrt(14.0)));
    }
}

TEST_F(RayTracerFixture, TupleNormalize) {
    {
        const Tuple v = make_vector(4.0, 0.0, 0.0);
        EXPECT_EQ(v.normalize(), make_vector(1.0, 0.0, 0.0));
    }
    {
        const Tuple v = make_vector(1.0, 2.0, 3.0);
        const double sqrt_of_fourteen = std::sqrt(14.0);
        EXPECT_EQ(v.normalize(), make_vector(1.0 / sqrt_of_fourteen, 2.0 / sqrt_of_fourteen, 3.0 / sqrt_of_fourteen));
    }
    {
        const Tuple v = make_vector(1.0, 2.0, 3.0);
        EXPECT_TRUE(within_epsilon(v.normalize().magnitude(), 1.0));
    }
}

TEST_F(RayTracerFixture, TupleDotProduct) {
    const Tuple v1 = make_vector(1.0, 2.0, 3.0);
    const Tuple v2 = make_vector(2.0, 3.0, 4.0);
    EXPECT_EQ(v1.dot(v2), 20.0);
}

TEST_F(RayTracerFixture, TupleCrossProduct) {
    const Tuple v1 = make_vector(1.0, 2.0, 3.0);
    const Tuple v2 = make_vector(2.0, 3.0, 4.0);
    const Tuple expected = make_vector(-1.0, 2.0, -1.0);
    EXPECT_EQ(v1.cross(v2), expected);
    EXPECT_EQ(v2.cross(v1), -expected);
}

TEST_F(RayTracerFixture, ColorBasic) {
    const Color c1 = make_color(-0.5, 0.4, 1.7);
    EXPECT_EQ(c1.red(), -0.5);
    EXPECT_EQ(c1.green(), 0.4);
    EXPECT_EQ(c1.blue(), 1.7);
}

TEST_F(RayTracerFixture, ColorAddition) {
    const Color c1 = make_color(3.0, -2.0, 5.0);
    const Color c2 = make_color(-2.0, 3.0, 1.0);

    EXPECT_EQ(c1 + c2, make_color(1.0, 1.0, 6.0));
}

TEST_F(RayTracerFixture, ColorSubtraction) {
    {
        const Color c1 = make_color(3.0, 2.0, 1.0);
        const Color c2 = make_color(5.0, 6.0, 7.0);
        EXPECT_EQ(c1 - c2, make_color(-2.0, -4.0, -6.0));
    }
    {
        // TODO unsure if this makes sense (negative color)
        const Color c1 = make_color(0.0, 0.0, 0.0);
        const Color c2 = make_color(5.0, 6.0, 7.0);
        EXPECT_EQ(c1 - c2, make_color(-5.0, -6.0, -7.0));
    }
}

TEST_F(RayTracerFixture, ColorScalarMultiply) {
    {
        // TODO do these values make sense for a color?
        const Color c = make_color(1.0, -2.0, 3.0);
        EXPECT_EQ(c * 3.5, make_color(3.5, -7.0, 10.5));
    }
}

TEST_F(RayTracerFixture, ColorElementWiseProduct) {
    {
        const Color c1 = make_color(1.0, 0.2, 0.4);
        const Color c2 = make_color(0.9, 1.0, 0.1);

        EXPECT_EQ(c1 * c2, make_color(0.9, 0.2, 0.04));
    }
}

TEST_F(RayTracerFixture, CanvasBasic) {
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

TEST_F(RayTracerFixture, CanvasWritePixel) {
    {
        constexpr size_t width = 100;
        constexpr size_t height = 100;
        Canvas<width, height> canvas;

        const Color red = make_color(1.0, 0.0, 0.0);
        canvas.write_pixel(2, 3, red);
        EXPECT_EQ(canvas.pixel_at(2, 3), red);
    }
}

TEST_F(RayTracerFixture, PPMHeaderConstruction) {
    constexpr size_t width = 100;
    constexpr size_t height = 200;
    const Canvas<width, height> canvas;

    // Check that the PPM header is at the very beginning of the PPM string.
    const std::string expected = "P3\n100 200\n255\n";
    EXPECT_EQ(canvas.to_ppm().find(expected), 0);
}

TEST_F(RayTracerFixture, PPMPixelConstruction) {
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

TEST_F(RayTracerFixture, PPMSeventyCharLimit) {
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

TEST_F(RayTracerFixture, PPMFileSaving) {
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

TEST_F(RayTracerFixture, MatrixFourByFourConstruction) {
    constexpr size_t w = 4;
    constexpr size_t h = 4;
    auto cells = std::array<std::array<double, w>, h>{
            {{1.0, 2.0, 3.0, 4.0}, {5.5, 6.5, 7.5, 8.5}, {9.0, 10.0, 11.0, 12.0}, {13.5, 14.5, 15.5, 16.5}}
    };
    auto m = Matrix<h, w>{cells};
    EXPECT_EQ(m.cells[0][0], 1.0);
    EXPECT_EQ(m.cells[0][3], 4.0);
    EXPECT_EQ(m.cells[1][0], 5.5);
    EXPECT_EQ(m.cells[1][2], 7.5);
    EXPECT_EQ(m.cells[2][2], 11.0);
    EXPECT_EQ(m.cells[3][0], 13.5);
    EXPECT_EQ(m.cells[3][2], 15.5);
}

TEST_F(RayTracerFixture, MatrixTwoByTwoConstruction) {
    constexpr size_t w = 2;
    constexpr size_t h = 2;
    auto cells = std::array<std::array<double, w>, h>{
            {{-3.0, 5.0}, {1.0, -2.0}}
    };
    auto m = Matrix<h, w>{cells};
    EXPECT_EQ(m.cells[0][0], -3.0);
    EXPECT_EQ(m.cells[0][1], 5.0);
    EXPECT_EQ(m.cells[1][0], 1.0);
    EXPECT_EQ(m.cells[1][1], -2.0);
}

TEST_F(RayTracerFixture, MatrixThreeByThreeConstruction) {
    constexpr size_t w = 3;
    constexpr size_t h = 3;
    auto cells = std::array<std::array<double, w>, h>{
            {{-3.0, 5.0, 0.0}, {1.0, -2.0, -7.0}, {0.0, 1.0, 1.0}}
    };
    auto m = Matrix<h, w>{cells};
    EXPECT_EQ(m.cells[0][0], -3.0);
    EXPECT_EQ(m.cells[1][1], -2.0);
    EXPECT_EQ(m.cells[2][2], 1.0);
}
