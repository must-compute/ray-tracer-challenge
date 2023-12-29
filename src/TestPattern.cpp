#include "TestPattern.h"

Color TestPattern::pattern_at(const Tuple &point) const {
  return Color{point.x(), point.y(), point.z()};
}
