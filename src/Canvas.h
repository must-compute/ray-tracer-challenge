
#ifndef RAY_TRACER_CHALLENGE_CANVAS_H
#define RAY_TRACER_CHALLENGE_CANVAS_H

#include <cassert>
#include <cstddef>
#include <array>
#include <string>
#include <cmath>
#include <sstream>
#include "Color.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

template<size_t WIDTH, size_t HEIGHT>
class Canvas {
public:
  [[nodiscard]] consteval size_t width() const {
    return WIDTH;
  }

  [[nodiscard]] consteval size_t height() const {
    return HEIGHT;
  }

  std::array<std::array<Color, WIDTH>, HEIGHT> pixels() const {
    return pixels_;
  }

  void write_pixel(size_t x, size_t y, const Color color) noexcept {
    pixels_[y][x] = color;
  }

  [[nodiscard]] Color pixel_at(size_t x, size_t y) const noexcept {
    return pixels_[y][x];
  }

  [[nodiscard]] std::string to_ppm() const {
    const std::string header = std::string("P3\n")
        .append(std::to_string(WIDTH))
        .append(" ")
        .append(std::to_string(HEIGHT))
        .append("\n255\n");

    return header + ppm_body();
  }

  [[nodiscard]] std::string ppm_body() const {
    std::vector<std::string> lines;
    for (size_t row = 0; row < HEIGHT; ++row) {
      std::stringstream ss;

      for (size_t col = 0; col < WIDTH; ++col) {
        for (const double color_value : pixels_[row][col].rgb()) {
          const double clamped = std::clamp(color_value, 0.0, 1.0);
          const int remapped = static_cast<int>(std::round(std::lerp(0, 255, clamped)));
          ss << remapped << ' ';
        }
      }

      std::string line = ss.str();
      // Trim the last space. We'll put a newline there instead (later).
      if (!line.empty() && line.back() == ' ') {
        line.pop_back();
      }

      // if length > 70 split over two lines and push back two lines instead of one
      if (line.size() > 70) {
        // keep looking left until we find a place to insert the newline break.
        size_t index = 70;
        while (line[index] != ' ' && line[index] != '\n' && index > 0) {
          index--;
        }
        if (index != 0) {
          line.replace(index, 1, "\n");
        } else {
          assert((false, "couldn't hard-wrap!"));
        }
      }

      lines.push_back(line);
    }

    std::string assembled;
    for (const auto &line : lines) {
      assembled.append(line + "\n");
    }
    return assembled;
  }

  void to_file(const std::filesystem::path &path) const {
    std::ofstream outfile{path};
    outfile << to_ppm();
    outfile.close();
  }

private:

  std::array<std::array<Color, WIDTH>, HEIGHT> pixels_;
};

#endif //RAY_TRACER_CHALLENGE_CANVAS_H
