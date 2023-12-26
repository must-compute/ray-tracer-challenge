#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include "Matrix.h"
#include "Triangle.h"
#include "Tuple.h"
#include "WavefrontOBJ.h"

TEST(WavefrontObj, IgnoringUnrecognizedLines) {
    const std::string text = R"(Line 1
Line 2
Line 3)";
    const auto filepath = std::filesystem::temp_directory_path() / "invalid.obj";
    std::ofstream file{filepath};
    file << text;
    file.close();

    const auto obj = WavefrontOBJ::parse_obj_file(filepath);
    EXPECT_EQ(obj.ignored_lines().size(), 3);
}

TEST(WavefrontObj, VertexRecords) {
    const std::string text = R"(v -1 1 0
v -1.0000 0.5000 0.0000
v 1 0 0
v 1 1 0)";
    const auto filepath = std::filesystem::temp_directory_path() / "valid.obj";
    std::ofstream file{filepath};
    file << text;
    file.close();

    const auto obj = WavefrontOBJ::parse_obj_file(filepath);

    // We're intentionally using a 1-based instead of a 0-based index, per the file format.
    ASSERT_EQ(obj.vertices().size(), 5);
    EXPECT_EQ(obj.vertices()[1], make_point(-1.0, 1.0, 0.0));
    EXPECT_EQ(obj.vertices()[2], make_point(-1.0, 0.5, 0.0));
    EXPECT_EQ(obj.vertices()[3], make_point(1.0, 0.0, 0.0));
    EXPECT_EQ(obj.vertices()[4], make_point(1.0, 1.0, 0.0));
}

TEST(WavefrontObj, ParsingTriangleFaces) {
    const std::string text = R"(v -1 1 0
v -1 0 0
v 1 0 0
v 1 1 0

f 1 2 3
f 1 3 4)";

    const auto filepath = std::filesystem::temp_directory_path() / "valid.obj";
    std::ofstream file{filepath};
    file << text;
    file.close();
    const auto obj = WavefrontOBJ::parse_obj_file(filepath);

    const auto group = obj.default_group();
    ASSERT_EQ(group->children().size(), 2);
    const auto t1 = std::dynamic_pointer_cast<Triangle>(group->children()[0]);
    const auto t2 = std::dynamic_pointer_cast<Triangle>(group->children()[1]);

    // We're intentionally using a 1-based instead of a 0-based index, per the file format.
    ASSERT_EQ(obj.vertices().size(), 5);
    EXPECT_EQ(t1->p1(), obj.vertices()[1]);
    EXPECT_EQ(t1->p2(), obj.vertices()[2]);
    EXPECT_EQ(t1->p3(), obj.vertices()[3]);
    EXPECT_EQ(t2->p1(), obj.vertices()[1]);
    EXPECT_EQ(t2->p2(), obj.vertices()[3]);
    EXPECT_EQ(t2->p3(), obj.vertices()[4]);
}

TEST(WavefrontObj, TriangulatingPolygons) {
    const std::string text = R"(v -1 1 0
v -1 0 0
v 1 0 0
v 1 1 0
v 0 2 0

f 1 2 3 4 5)";

    const auto filepath = std::filesystem::temp_directory_path() / "polygon.obj";
    std::ofstream file{filepath};
    file << text;
    file.close();
    const auto obj = WavefrontOBJ::parse_obj_file(filepath);

    const auto group = obj.default_group();
    ASSERT_EQ(group->children().size(), 3);
    const auto t1 = std::dynamic_pointer_cast<Triangle>(group->children()[0]);
    const auto t2 = std::dynamic_pointer_cast<Triangle>(group->children()[1]);
    const auto t3 = std::dynamic_pointer_cast<Triangle>(group->children()[2]);

    // We're intentionally using a 1-based instead of a 0-based index, per the file format.
    ASSERT_EQ(obj.vertices().size(), 6);
    EXPECT_EQ(t1->p1(), obj.vertices()[1]);
    EXPECT_EQ(t1->p2(), obj.vertices()[2]);
    EXPECT_EQ(t1->p3(), obj.vertices()[3]);
    EXPECT_EQ(t2->p1(), obj.vertices()[1]);
    EXPECT_EQ(t2->p2(), obj.vertices()[3]);
    EXPECT_EQ(t2->p3(), obj.vertices()[4]);
    EXPECT_EQ(t3->p1(), obj.vertices()[1]);
    EXPECT_EQ(t3->p2(), obj.vertices()[4]);
    EXPECT_EQ(t3->p3(), obj.vertices()[5]);
}
