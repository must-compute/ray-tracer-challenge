#ifndef RAY_TRACER_CHALLENGE_PATTERN_H
#define RAY_TRACER_CHALLENGE_PATTERN_H

#include "Color.h"
#include "Tuple.h"
#include "Transformations.h"

class Shape;

class Pattern {
public:
  Pattern();

  Pattern(const Color &a, const Color &b);

  virtual ~Pattern() = default;

  bool operator==(const Pattern &other) const = default;

  [[nodiscard]] Color a() const;

  [[nodiscard]] Color b() const;

  [[nodiscard]] tf::Transform transform() const;

  void set_transform(const tf::Transform &t);

  [[nodiscard]] Color pattern_at_shape(const Shape &object, const Point &world_point) const;

protected:
  Color a_;
  Color b_;
  tf::Transform transform_;

  virtual Color pattern_at(const Point &point) const = 0;
};

#endif //RAY_TRACER_CHALLENGE_PATTERN_H
