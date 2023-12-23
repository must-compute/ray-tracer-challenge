#include <gtest/gtest.h>


#include "Bounds.h"
#include "Group.h"
#include "Sphere.h"

TEST(Bounds, CreateBoundsGroup) {
    const auto s = std::make_shared<Sphere>(Sphere{});
    auto g = Group::make_group();
    g->add_child(s);
    const auto b = g->make_bounds();

    EXPECT_TRUE(false);
}

