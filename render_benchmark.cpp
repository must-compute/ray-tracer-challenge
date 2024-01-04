#include <benchmark/benchmark.h>
#include <numbers>
#include <memory>

#include "CSG.h"
#include "Intersection.h"
#include "Sphere.h"
#include "Ray.h"
#include "World.h"
#include "Camera.h"
#include "StripePattern.h"
#include "Cube.h"

using std::numbers::pi;

// TODO put these in a fixture
World get_world() {
  auto world = World{};
  auto cube = std::make_shared<Cube>(Cube{});
  auto cube_material = Material{};
  cube_material.color = Color{1.0, 0.0, 0.0};
  cube->set_material(cube_material);

  cube->set_transform(tf::translation(0.0, 1.0, 0.0) * tf::rotation_y(pi / 4.0));

  auto sphere = std::make_shared<Sphere>(Sphere{});
  sphere->set_transform(tf::translation(0.0, 1.5, -1.0));
  auto right_material = Material{};
  right_material.color = Color{0.0, 1.0, 0.1};
  right_material.ambient = 0.1;
  right_material.diffuse = 0.7;
  right_material.specular = 0.3;
  right_material.reflective = 0.1;
  sphere->set_material(right_material);

  auto csg = CSG::make_csg(CSGOperation::Difference, cube, sphere);
  world.objects.push_back(csg);

  return world;

}

template<size_t WIDTH, size_t HEIGHT>
Camera<WIDTH, HEIGHT> get_camera() {
  auto camera = Camera<WIDTH, HEIGHT>{pi / 3.0};
  camera.set_transform(
      tf::view_transform(Point{1.0, 5.0, -5.0}, Point{0.0, 1.0, 0.0}, Vector{0.0, 1.0, 0.0}));
  return camera;
}

static void BM_world_render(benchmark::State &state) {
  auto camera = get_camera<500, 500>();
  auto world = get_world();

  const size_t n_threads = state.range(0);
  for (auto _ : state) {
    auto canvas = camera.render(world, n_threads);
    benchmark::DoNotOptimize(canvas);
  }
}

// TODO parameterize on the number of objects in the world (randomly place objects with random material). Use a fixed random seed.
// TODO also parameterize on the canvas size.
// Parameterize the function on the thread count.
BENCHMARK(BM_world_render)->Repetitions(10)->ReportAggregatesOnly(true)
    ->Unit(benchmark::kMillisecond)->UseRealTime()->Arg(1)->Arg(4)->Arg(8)->Arg(10);
BENCHMARK_MAIN();