#include "TestPattern.h"

Color TestPattern::pattern_at(const Point &point) const {
  return Color{point.x(), point.y(), point.z()};
}
