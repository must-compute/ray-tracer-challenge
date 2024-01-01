#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include "Triangle.h"
#include "SmoothTriangle.h"
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
  EXPECT_EQ(obj.vertices()[1], (Point{-1.0, 1.0, 0.0}));
  EXPECT_EQ(obj.vertices()[2], (Point{-1.0, 0.5, 0.0}));
  EXPECT_EQ(obj.vertices()[3], (Point{1.0, 0.0, 0.0}));
  EXPECT_EQ(obj.vertices()[4], (Point{1.0, 1.0, 0.0}));
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

TEST(WavefrontObj, TrianglesInGroups) {
  const std::string text = R"(v -1 1 0
v -1 0 0
v 1 0 0
v 1 1 0

g FirstGroup
f 1 2 3
g SecondGroup
f 1 3 4)";

  const auto filepath = std::filesystem::temp_directory_path() / "triangles.obj";
  std::ofstream file{filepath};
  file << text;
  file.close();
  const auto obj = WavefrontOBJ::parse_obj_file(filepath);

  EXPECT_TRUE(obj.default_group()->children().empty());

  const auto named_groups = obj.named_groups();
  ASSERT_EQ(named_groups.size(), 2);
  const auto g1 = named_groups.at("FirstGroup");
  const auto g2 = named_groups.at("SecondGroup");

  ASSERT_EQ(g1->children().size(), 1);
  ASSERT_EQ(g2->children().size(), 1);
  const auto t1 = std::dynamic_pointer_cast<Triangle>(g1->children()[0]);
  const auto t2 = std::dynamic_pointer_cast<Triangle>(g2->children()[0]);

  // We're intentionally using a 1-based instead of a 0-based index, per the file format.
  ASSERT_EQ(obj.vertices().size(), 5);
  EXPECT_EQ(t1->p1(), obj.vertices()[1]);
  EXPECT_EQ(t1->p2(), obj.vertices()[2]);
  EXPECT_EQ(t1->p3(), obj.vertices()[3]);
  EXPECT_EQ(t2->p1(), obj.vertices()[1]);
  EXPECT_EQ(t2->p2(), obj.vertices()[3]);
  EXPECT_EQ(t2->p3(), obj.vertices()[4]);
}

TEST(WavefrontObj, ConvertingObjFileToGroup) {
  const std::string text = R"(v -1 1 0
v -1 0 0
v 1 0 0
v 1 1 0

g FirstGroup
f 1 2 3
g SecondGroup
f 1 3 4)";

  const auto filepath = std::filesystem::temp_directory_path() / "triangles.obj";
  std::ofstream file{filepath};
  file << text;
  file.close();
  const auto obj = WavefrontOBJ::parse_obj_file(filepath);

  const auto group = obj.to_group();

  const auto first_group = obj.named_groups()["FirstGroup"];
  const auto second_group = obj.named_groups()["SecondGroup"];

  ASSERT_TRUE(std::find(group->children().begin(), group->children().end(), first_group) != group->children().end());
  ASSERT_TRUE(std::find(group->children().begin(), group->children().end(), second_group) != group->children().end());
}

TEST(WavefrontObj, VertexNormalRecords) {
  const std::string text = R"(vn 0 0 1
vn 0.707 0 -0.707
vn 1 2 3)";

  const auto filepath = std::filesystem::temp_directory_path() / "normals.obj";
  std::ofstream file{filepath};
  file << text;
  file.close();
  const auto obj = WavefrontOBJ::parse_obj_file(filepath);

  // NOTE: because this is 1-indexed, there are 4 elements (even though there are 3 normals).
  ASSERT_EQ(obj.normals().size(), 4);
  EXPECT_EQ(obj.normals()[1], (Vector{0.0, 0.0, 1.0}));
  EXPECT_EQ(obj.normals()[2], (Vector{0.707, 0.0, -0.707}));
  EXPECT_EQ(obj.normals()[3], (Vector{1.0, 2.0, 3.0}));
}

TEST(WavefrontObj, FacesWithNormals) {
  const std::string text = R"(v 0 1 0
v -1 0 0
v 1 0 0

vn -1 0 0
vn 1 0 0
vn 0 1 0

f 1//3 2//1 3//2
f 1/0/3 2/102/1 3/14/2
)";

  const auto filepath = std::filesystem::temp_directory_path() / "vertex_normals.obj";
  std::ofstream file{filepath};
  file << text;
  file.close();
  const auto obj = WavefrontOBJ::parse_obj_file(filepath);

  const auto g = obj.default_group();
  ASSERT_EQ(g->children().size(), 2);
  const auto t1 = std::dynamic_pointer_cast<SmoothTriangle>(g->children()[0]);
  const auto t2 = std::dynamic_pointer_cast<SmoothTriangle>(g->children()[1]);

  ASSERT_TRUE(t1);
  ASSERT_TRUE(t2);

  // NOTE: because this is 1-indexed, there are 4 elements (even though there are 3 vertices).
  const auto &vertices = obj.vertices();
  ASSERT_EQ(vertices.size(), 4);
  EXPECT_EQ(t1->p1(), vertices[1]);
  EXPECT_EQ(t1->p2(), vertices[2]);
  EXPECT_EQ(t1->p3(), vertices[3]);

  // NOTE: because this is 1-indexed, there are 4 elements (even though there are 3 normals).
  const auto &normals = obj.normals();
  ASSERT_EQ(normals.size(), 4);
  EXPECT_EQ(t1->n1(), normals[3]);
  EXPECT_EQ(t1->n2(), normals[1]);
  EXPECT_EQ(t1->n3(), normals[2]);

  EXPECT_EQ(*t1, *t2);
}
