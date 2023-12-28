#include "TestPattern.h"

Color TestPattern::pattern_at(const Tuple &point) const {
  return make_color(point.x(), point.y(), point.z());
}
