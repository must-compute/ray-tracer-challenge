#include <gtest/gtest.h>

#include "Color.h"
#include "Tuple.h"
#include "PointLight.h"

TEST(Lights, PointLightHasPosAndIntensity) {
  const auto intensity = Color{1.0, 1.0, 1.0};
  const auto position = make_point(0.0, 0.0, 0.0);

  const auto light = PointLight(position, intensity);
  EXPECT_EQ(light.position(), position);
  EXPECT_EQ(light.intensity(), intensity);
}
