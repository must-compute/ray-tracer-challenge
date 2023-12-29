#include <filesystem>
#include <numbers>
#include <memory>

#include "CSG.h"
#include "Intersection.h"
#include "Sphere.h"
#include "Plane.h"
#include "Ray.h"
#include "World.h"
#include "Camera.h"
#include "StripePattern.h"
#include "RingPattern.h"
#include "Cube.h"
#include "Cone.h"
#include "WavefrontOBJ.h"

int main() {
  using std::numbers::pi;

  const size_t width = 500;
  const size_t height = 500;
  const Color white = make_color(1.0, 1.0, 1.0);
  const Color black = make_color(0.0, 0.0, 0.0);
  auto world = World{};

  auto floor = Plane{};
  auto floor_material = Material{};
  floor_material.ambient = 0.4;
  floor_material.diffuse = 0.9;
  floor_material.pattern = std::make_shared<StripePattern>(
      StripePattern{make_color(0.7, 0.7, 0.7), make_color(0.3, 0.3, 0.3)});
  floor.set_material(floor_material);
  world.objects.push_back(std::make_shared<Plane>(floor));

//    auto left_wall_material = Material{};
//    left_wall_material.color = make_color(0.4, 0.4, 1.0);
//    left_wall_material.diffuse = 0.9;
//    left_wall_material.ambient = 0.9;
//    auto left_wall = Plane{};
//    left_wall.set_transform(tf::translation(0.0, 0.0, 5.0) * tf::rotation_y(-pi / 4.0) * tf::rotation_x(pi / 2.0));
//    left_wall.set_material(left_wall_material);
  //world.objects.push_back(std::make_shared<Plane>(left_wall));

//    auto dome_material = Material{};
//    auto dome = Sphere{};
//    dome.set_transform(tf::scaling(100.0, 100.0, 100.0));
//    world.objects.push_back(std::make_shared<Sphere>(dome));
//
//    auto middle_sphere = Sphere{};
//    middle_sphere.set_transform(tf::translation(-0.5, 1.0, 0.5));
//    auto middle_material = Material{};
//    middle_material.color = make_color(0.9, 0.1, 0.1);
//    middle_material.ambient = 0.1;
//    middle_material.diffuse = 0.1;
//    middle_material.specular = 1.0;
//    middle_material.shininess = 300.0;
//    middle_material.refractive_index = 1.3;
//    middle_material.reflective = 0.9;
//    middle_material.transparency = 1.0;
//    middle_sphere.set_material(middle_material);
//    world.objects.push_back(std::make_shared<Sphere>(middle_sphere));
//
//    auto cube = Cube{};
//    auto cube_material = Material{};
//    cube_material.color = make_color(0.0, 1.0, 0.0);
//    cube.set_material(cube_material);
//
//    cube.set_transform(tf::translation(-2.0, 0.5, 1.5) * tf::rotation_y(pi / 8.0));
//    world.objects.push_back(std::make_shared<Cube>(cube));
//
//    auto right_sphere = Sphere{};
//    right_sphere.set_transform(tf::translation(1.5, 0.5, 1.5) * tf::scaling(0.5, 0.5, 0.5));
//    auto right_material = Material{};
//    right_material.color = make_color(0.0, 1.0, 0.1);
//    right_material.ambient = 0.1;
//    right_material.diffuse = 0.7;
//    right_material.specular = 0.3;
//    right_material.reflective = 0.1;
//    right_sphere.set_material(right_material);
//    world.objects.push_back(std::make_shared<Sphere>(right_sphere));
//
//    auto cone = std::make_shared<Cone>(Cone{});
//    cone->set_minimum(0.0);
//    cone->set_maximum(1.0);
//    cone->set_transform(tf::translation(2.0, 0.0, 0.0) * tf::scaling(0.4, 1.5, 0.4));
//    auto cone_material = Material{};
//    cone_material.color = make_color(1.0, 1.0, 0.0);
//    cone_material.ambient = 0.3;
//    cone_material.diffuse = 0.6;
//    cone_material.specular = 0.3;
//    cone_material.reflective = 0.0;
//    cone->set_material(cone_material);
//    world.objects.push_back(cone);
//
  world.light = PointLight{make_point(-10.0, 10.0, -10.0), white};

  /*
  //const auto obj = WavefrontOBJ::parse_obj_file(std::filesystem::path("../assets/test_file.obj"));
  const auto obj = WavefrontOBJ::parse_obj_file(std::filesystem::path("../assets/another_test.obj"));
  auto group = obj.to_group();

  group->set_transform(tf::translation(0.0, 5.0, 0.0) * tf::rotation_x(-pi / 2.0) * tf::rotation_z(pi / 6.0));

  world.objects.push_back(group);
  */

  auto cube = std::make_shared<Cube>(Cube{});
  auto cube_material = Material{};
  cube_material.color = make_color(0.0, 1.0, 0.0);
  cube->set_material(cube_material);

  cube->set_transform(tf::translation(0.0, 1.0, 0.0) * tf::rotation_y(pi / 4.0));

  auto sphere = std::make_shared<Sphere>(Sphere{});
  sphere->set_transform(tf::translation(0.0, 1.5, -1.0));
  //sphere->set_transform(tf::translation(1.5, 0.5, 1.5) * tf::scaling(0.5, 0.5, 0.5));
  auto right_material = Material{};
  right_material.color = make_color(0.0, 1.0, 0.1);
  right_material.ambient = 0.1;
  right_material.diffuse = 0.7;
  right_material.specular = 0.3;
  right_material.reflective = 0.1;
  sphere->set_material(right_material);

  auto csg = CSG::make_csg(CSGOperation::Difference, cube, sphere);
  world.objects.push_back(csg);

  auto camera = Camera<width, height>{pi / 3.0};
  camera.set_transform(
      tf::view_transform(make_point(1.0, 5.0, -5.0), make_point(0.0, 1.0, 0.0), make_vector(0.0, 1.0, 0.0)));

  auto canvas = camera.render(world);

  std::filesystem::path temp_path = "./output.ppm";
  canvas.to_file(temp_path);
  return 0;
}
