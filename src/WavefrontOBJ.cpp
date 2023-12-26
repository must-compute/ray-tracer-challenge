#include "WavefrontOBJ.h"

#include <fstream>
#include <sstream>
#include <string>

#include "Tuple.h"
#include "Triangle.h"

std::vector<std::string> split(const std::string &str) {
    std::istringstream iss(str);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

WavefrontOBJ::WavefrontOBJ() : default_group_{Group::make_group()} {}

WavefrontOBJ WavefrontOBJ::parse_obj_file(const std::filesystem::path &path) {
    WavefrontOBJ obj{};
    std::vector<std::string> ignored_lines{};
    std::vector<Tuple> vertices{};
    vertices.push_back(make_point(0.0, 0.0, 0.0)); // TODO is there a better way to make vertices index starting at 1?

    std::ifstream input_file{path};

    std::string line;
    while (std::getline(input_file, line)) {
        auto tokens = split(line);
        if (tokens.empty()) {
            continue;
        }
        if (tokens.front() == "v") { // vertex
            assert(tokens.size() == 4); // v followed by 3 numbers
            std::vector<double> vertex_tokens(tokens.size() - 1); // skip the initial v
            std::transform(tokens.begin() + 1, // skip initial v
                           tokens.end(),
                           vertex_tokens.begin(),
                           [](const std::string &v) { return std::stod(v); }
            ); // TODO handle conversion errors
            vertices.push_back(make_point(vertex_tokens[0], vertex_tokens[1], vertex_tokens[2]));
        } else if (tokens.front() == "f") { // face
            assert(tokens.size() == 4); // f followed by 3 numbers
            std::vector<size_t> face_tokens(tokens.size() - 1); // skip the initial f
            std::transform(tokens.begin() + 1, // skip initial f
                           tokens.end(),
                           face_tokens.begin(),
                           [](const std::string &f) { return std::stoi(f); }
            ); // TODO handle conversion errors
            // TODO handle indexing errors
            obj.add_triangle(Triangle{vertices[face_tokens[0]], vertices[face_tokens[1]], vertices[face_tokens[2]]});
        } else {
            ignored_lines.push_back(line);
        }
    }
    input_file.close();

    obj.set_vertices(vertices);
    obj.set_ignored_lines(ignored_lines);

    return obj;
}

std::vector<std::string> WavefrontOBJ::ignored_lines() const {
    return ignored_lines_;
}

std::shared_ptr<Group> WavefrontOBJ::default_group() const {
    return default_group_;
}

std::vector<Tuple> WavefrontOBJ::vertices() const {
    return vertices_;
}

void WavefrontOBJ::set_ignored_lines(const std::vector<std::string> &ignored_lines) {
    ignored_lines_ = ignored_lines;
}

void WavefrontOBJ::set_vertices(const std::vector<Tuple> &vertices) {
    vertices_ = vertices;
}

void WavefrontOBJ::add_triangle(const Triangle &triangle) {
    default_group_->add_child(std::make_shared<Triangle>(triangle));
}
