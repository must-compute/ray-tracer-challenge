#include "WavefrontOBJ.h"

#include <fstream>
#include <sstream>
#include <string>
#include <variant>

#include "Tuple.h"
#include "Triangle.h"
#include "SmoothTriangle.h"

std::vector<std::string> split(const std::string &str, const char delimiter) {
  std::istringstream iss(str);
  std::vector<std::string> tokens{};
  std::string token{};
  while (std::getline(iss, token, delimiter)) {
    tokens.push_back(token);
  }

  return tokens;
}

std::vector<std::shared_ptr<Triangle>> parse_f_line(const std::vector<std::string> &tokens,
                                                    const std::vector<Point> &vertices,
                                                    const std::vector<Vector> &normals) {
  // Handle interpolated triangle case. Returns a single SmoothTriangle (shared_ptr).
  // Example input:
  // f 1/2/3 4/5/6 7//8
  // Looking at "1/2/3", the first number 1 is the vertex index, the second number 2 is ignored, and the third number is the vertex normal index.
  if (tokens[1].find('/') != std::string::npos) {
    std::vector<std::string> vertex_info = split(tokens[1], '/');
    assert(vertex_info.size() == 3);
    const auto first_vertex = vertex_info[0];
    const auto first_normal = vertex_info[2];

    vertex_info = split(tokens[2], '/');
    assert(vertex_info.size() == 3);
    const auto second_vertex = vertex_info[0];
    const auto second_normal = vertex_info[2];

    vertex_info = split(tokens[3], '/');
    assert(vertex_info.size() == 3);
    const auto third_vertex = vertex_info[0];
    const auto third_normal = vertex_info[2];

    // Only return one SmoothTriangle
    return {std::make_shared<SmoothTriangle>(
        SmoothTriangle{vertices[std::stoi(first_vertex)], vertices[std::stoi(second_vertex)],
                       vertices[std::stoi(third_vertex)],
                       normals[std::stoi(first_normal)], normals[std::stoi(second_normal)],
                       normals[std::stoi(third_normal)]})};
  } else {
    // In the general case, we return one or more Triangles (no interpolation).
    // Example input:
    // f 1 2 3 4 5
    // Each of the numbers is a vertex index. If more than 3 vertex indices are specified, we use fan triangulation to
    // infer multiple triangle faces.
    std::vector<size_t> face_tokens(tokens.size() - 1); // skip initial f
    std::transform(tokens.begin() + 1, // skip initial f
                   tokens.end(),
                   face_tokens.begin(),
                   [](const std::string &f) { return std::stoi(f); }
    ); // TODO handle conversion errors

    // Fan triangulation algorithm, returns many Triangles.
    // Given a line like "f 1 2 3 4 5", add these triangles:
    //  Triangle{ vertices[1], vertices[2], vertices[3] }
    //  Triangle{ vertices[1], vertices[3], vertices[4] }
    //  Triangle{ vertices[1], vertices[4], vertices[5] }
    std::vector<std::shared_ptr<Triangle>> triangles{};
    for (size_t index = 1; index <= face_tokens.size() - 2; ++index) {
      triangles.push_back(std::make_shared<Triangle>(Triangle{vertices[face_tokens[0]],
                                                              vertices[face_tokens[index]],
                                                              vertices[face_tokens[index + 1]]}));

    }
    return triangles;
  }
}

WavefrontOBJ::WavefrontOBJ() : default_group_{Group::make_group()} {}

WavefrontOBJ WavefrontOBJ::parse_obj_file(const std::filesystem::path &path) {
  WavefrontOBJ obj{};
  std::vector<std::string> ignored_lines{};
  std::vector<Point> vertices{};
  vertices.push_back(make_point(0.0, 0.0, 0.0)); // TODO is there a better way to make vertices index starting at 1?
  std::vector<Vector> normals{};
  normals.push_back(make_vector(0.0, 0.0, 0.0)); // TODO is there a better way to make normals index starting at 1?

  std::optional<std::string> current_group{};

  std::ifstream input_file{path};

  std::string line;
  while (std::getline(input_file, line)) {
    // For each line, do one of the following:
    // 1- nothing (empty line)
    // 2- add vertex (v statement)
    // 3- add vertex normal (vn statement)
    // 4- set current_group (g statement)
    // 5- add Triangle(s) or SmoothTriangle (f statement)
    // 6- add line to ignored_lines (unimplemented statement)
    const std::vector<std::string> tokens = split(line, ' ');
    // Case 1
    if (tokens.empty()) {
      continue;
    }
    if (tokens.front() == "v") { // Case 2: vertex
      assert(tokens.size() == 4); // v followed by 3 numbers
      vertices.push_back(make_point(std::stod(tokens[1]), std::stod(tokens[2]), std::stod(tokens[3])));
    } else if (tokens.front() == "vn") { // Case 3: vertex normal (vn)
      assert(tokens.size() == 4); // vn followed by 3 numbers
      normals.push_back(make_vector(std::stod(tokens[1]), std::stod(tokens[2]), std::stod(tokens[3])));
    } else if (tokens.front() == "g") { // Case 4: group
      assert(tokens.size() == 2);
      current_group = tokens[1];
    } else if (tokens.front() == "f") { // Case 5: face
      assert(tokens.size() >= 3); // f followed by at least 3 numbers or expressions
      const auto triangles = parse_f_line(tokens, vertices, normals);
      for (const auto &triangle : triangles) {
        obj.add_triangle(triangle, current_group);
      }
    } else {
      ignored_lines.push_back(line);
    }
  }
  input_file.close();

  obj.set_vertices(vertices);
  obj.set_normals(normals);
  obj.set_ignored_lines(ignored_lines);

  return obj;
}

std::vector<std::string> WavefrontOBJ::ignored_lines() const {
  return ignored_lines_;
}

std::shared_ptr<Group> WavefrontOBJ::default_group() const {
  return default_group_;
}

std::unordered_map<std::string, std::shared_ptr<Group>> WavefrontOBJ::named_groups() const {
  return named_groups_;
}

std::vector<Point> WavefrontOBJ::vertices() const {
  return vertices_;
}

std::vector<Vector> WavefrontOBJ::normals() const {
  return normals_;
}

void WavefrontOBJ::set_ignored_lines(const std::vector<std::string> &ignored_lines) {
  ignored_lines_ = ignored_lines;
}

void WavefrontOBJ::set_vertices(const std::vector<Point> &vertices) {
  vertices_ = vertices;
}

void WavefrontOBJ::set_normals(const std::vector<Vector> &normals) {
  normals_ = normals;
}

void
WavefrontOBJ::add_triangle(const std::shared_ptr<Triangle> &triangle, const std::optional<std::string> &current_group) {

  if (!current_group) {
    default_group_->add_child(triangle);
    return;
  }

  const auto &key = *current_group;
  if (named_groups_.contains(key)) {
    named_groups_[key]->add_child(triangle);
  } else {
    auto group = Group::make_group();
    group->add_child(triangle);
    named_groups_[key] = group;
  }
}

std::shared_ptr<Group> WavefrontOBJ::to_group() const {
  auto result = Group::make_group();
  for (const auto &[_, group] : named_groups_) {
    result->add_child(group);
  }
  result->add_child(default_group_);
  return result;
}
