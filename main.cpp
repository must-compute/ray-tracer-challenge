#include <filesystem>
#include <numbers>
#include <memory>

#include "Intersection.h"
#include "Sphere.h"
#include "Plane.h"
#include "Ray.h"
#include "World.h"
#include "Camera.h"
#include "StripePattern.h"
#include "RingPattern.h"


int main() {
    using std::numbers::pi;

    const size_t width = 250;
    const size_t height = 100;
    const Color white = make_color(1.0, 1.0, 1.0);
    const Color black = make_color(0.0, 0.0, 0.0);
    auto world = World{};

    auto floor = Plane{};
    auto floor_material = Material{};
    floor_material.color = make_color(1.0, 0.9, 0.9);
    floor_material.specular = 0.0;
    floor_material.pattern = std::make_shared<StripePattern>(
            StripePattern{make_color(0.5, 0.2, 1.0), make_color(1.0, 0.2, 0.5)});
    floor.set_material(floor_material);
    world.objects.push_back(std::make_shared<Plane>(floor));

    auto left_wall_material = Material{};
    left_wall_material.color = make_color(0.4, 0.4, 1.0);
    left_wall_material.diffuse = 0.9;
    left_wall_material.ambient = 0.9;
    auto left_wall = Plane{};
    left_wall.set_transform(tf::translation(0.0, 0.0, 5.0) * tf::rotation_y(-pi / 4.0) * tf::rotation_x(pi / 2.0));
    left_wall.set_material(left_wall_material);
    //world.objects.push_back(std::make_shared<Plane>(left_wall));

    auto dome_material = Material{};
    auto dome = Sphere{};
    dome.set_transform(tf::scaling(100.0, 100.0, 100.0));
    world.objects.push_back(std::make_shared<Sphere>(dome));

    auto middle_sphere = Sphere{};
    middle_sphere.set_transform(tf::translation(-0.5, 1.0, 0.5));
    auto middle_material = Material{};
    middle_material.color = make_color(0.9, 0.1, 0.1);
    middle_material.ambient = 0.1;
    middle_material.diffuse = 0.1;
    middle_material.specular = 1.0;
    middle_material.shininess = 300.0;
    middle_material.refractive_index = 1.3;
    middle_material.reflective = 0.9;
    middle_material.transparency = 1.0;
    middle_sphere.set_material(middle_material);
    world.objects.push_back(std::make_shared<Sphere>(middle_sphere));

    auto right_sphere = Sphere{};
    right_sphere.set_transform(tf::translation(1.5, 1.0, -0.5) * tf::scaling(0.5, 0.5, 0.5));
    auto right_material = Material{};
    right_material.color = make_color(0.0, 1.0, 0.1);
    right_material.diffuse = 0.7;
    right_material.specular = 0.3;
    right_material.reflective = 0.8;
    right_sphere.set_material(right_material);
    world.objects.push_back(std::make_shared<Sphere>(right_sphere));

    auto left_sphere = Sphere{};
    left_sphere.set_transform(
            tf::translation(-1.5, 2.0, -0.75) * tf::rotation_z(pi / 4.0) * tf::scaling(1.0, 0.33, 0.33));
    auto left_material = Material{};
    left_material.color = make_color(0.2, 0.3, 1.0);
    left_material.diffuse = 0.7;
    left_material.specular = 0.3;
    left_sphere.set_material(left_material);
    world.objects.push_back(std::make_shared<Sphere>(left_sphere));

    world.light = PointLight{make_point(-10.0, 10.0, -10.0), white};

    auto camera = Camera<width, height>{pi / 3.0};
    camera.set_transform(
            tf::view_transform(make_point(0.0, 1.5, -5), make_point(0.0, 1.0, 0.0), make_vector(0.0, 1.0, 0.0)));

    auto canvas = camera.render(world);

    std::filesystem::path temp_path = "./output.ppm";
    canvas.to_file(temp_path);
    return 0;
}
