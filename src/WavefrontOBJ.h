#ifndef RAY_TRACER_CHALLENGE_WAVEFRONTOBJ_H
#define RAY_TRACER_CHALLENGE_WAVEFRONTOBJ_H

#include <filesystem>
#include <memory>
#include <unordered_map>

#include "Group.h"
#include "Tuple.h"
#include "Triangle.h"

class WavefrontOBJ {
public:
  [[nodiscard]] static WavefrontOBJ parse_obj_file(const std::filesystem::path &path);

  [[nodiscard]] std::vector<std::string> ignored_lines() const;

  [[nodiscard]] std::vector<Point> vertices() const;

  [[nodiscard]] std::vector<Vector> normals() const;

  [[nodiscard]] std::shared_ptr<Group> default_group() const;

  [[nodiscard]] std::unordered_map<std::string, std::shared_ptr<Group>> named_groups() const;

  [[nodiscard]] std::shared_ptr<Group> to_group() const;

  void set_ignored_lines(const std::vector<std::string> &ignored_lines);

  void set_vertices(const std::vector<Point> &vertices);

  void set_normals(const std::vector<Vector> &normals);

  void add_triangle(const std::shared_ptr<Triangle> &triangle, const std::optional<std::string> &current_group);

private:
  WavefrontOBJ();

  std::vector<std::string> ignored_lines_{};
  std::vector<Point> vertices_{};
  std::vector<Vector> normals_{};
  std::shared_ptr<Group> default_group_;
  std::unordered_map<std::string, std::shared_ptr<Group>> named_groups_;
};

#endif //RAY_TRACER_CHALLENGE_WAVEFRONTOBJ_H
