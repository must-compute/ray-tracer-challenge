#include <gtest/gtest.h>

#include "Material.h"

TEST(Material, DefaultMaterial) {
    auto m = Material{};
    EXPECT_EQ(m.color, make_color(1.0, 1.0, 1.0));
    EXPECT_EQ(m.ambient, 0.1);
    EXPECT_EQ(m.diffuse, 0.9);
    EXPECT_EQ(m.specular, 0.9);
    EXPECT_EQ(m.shininess, 200.0);

}
