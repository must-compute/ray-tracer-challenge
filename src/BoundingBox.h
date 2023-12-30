#ifndef BOUNDS_H
#define BOUNDS_H

#include <iostream>

#include "Tuple.h"
#include "Transformations.h"
#include "Ray.h"

// TODO add a debug-mode render function to show the wireframe bounding box
class BoundingBox {
public:
  BoundingBox();

  BoundingBox(const Point &minimum, const Point &maximum);

  void set_transform(const tf::Transform &transform);

  [[nodiscard]] Point minimum() const;

  [[nodiscard]] Point maximum() const;

  [[nodiscard]] bool contains_point(const Point &point) const;

  [[nodiscard]] bool contains_box(const BoundingBox &other) const;

  void add_point(const Point &point);

  void add_box(const BoundingBox &other);

  [[nodiscard]] bool intersects(const Ray &ray) const;

  [[nodiscard]] static std::pair<double, double> check_axis(double origin, double direction, double min, double max);

private:
  Point minimum_{};
  Point maximum_{};
};

#endif //BOUNDS_H
