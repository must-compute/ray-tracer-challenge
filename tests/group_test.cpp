#include <gtest/gtest.h>

#include "Group.h"
#include "Sphere.h"
#include "Transformations.h"
#include "TestShape.h"

TEST(Group, CreateNewGroup) {
    const auto g = Group{};
    EXPECT_EQ(g.transform(), tf::Transform::identity());
    EXPECT_EQ(g.children().size(), 0);
}

TEST(Group, AddingChildToGroup) {
    auto g = std::make_shared<Group>(Group{});
    const auto s = std::make_shared<TestShape>(TestShape{});
    ASSERT_EQ(g->children().size(), 0);
    Group::add_child(g, s);
    ASSERT_EQ(g->children().size(), 1);
    EXPECT_EQ(g->children()[0], s);
    ASSERT_TRUE(s->parent());
    EXPECT_EQ(*s->parent(), *g);
}

TEST(Group, IntersectingRayWithEmptyGroup) {
    auto g = Group{};
    const auto r = Ray{make_point(0.0, 0.0, 0.0), make_vector(0.0, 0.0, 1.0)};
    EXPECT_EQ(g.local_intersect(r).size(), 0);
}

TEST(Group, IntersectingRayWithNonEmptyGroup) {
    auto g = std::make_shared<Group>(Group{});
    auto s1 = std::make_shared<Sphere>(Sphere{});
    auto s2 = std::make_shared<Sphere>(Sphere{});
    auto s3 = std::make_shared<Sphere>(Sphere{});
    s2->set_transform(tf::translation(0.0, 0.0, -3.0));
    s3->set_transform(tf::translation(5.0, 0.0, 0.0));
    Group::add_child(g, s1);
    Group::add_child(g, s2);
    Group::add_child(g, s3);

    const auto r = Ray{make_point(0.0, 0.0, -5.0), make_vector(0.0, 0.0, 1.0)};
    const auto xs = g->local_intersect(r);
    ASSERT_EQ(xs.size(), 4);
    ASSERT_TRUE(xs[0].object);
    EXPECT_EQ(*xs[0].object, *s2);
    ASSERT_TRUE(xs[1].object);
    EXPECT_EQ(*xs[1].object, *s2);
    ASSERT_TRUE(xs[2].object);
    EXPECT_EQ(*xs[2].object, *s1);
    ASSERT_TRUE(xs[3].object);
    EXPECT_EQ(*xs[3].object, *s1);
}

TEST(Group, IntersectingTransformedGroup) {
    auto g = std::make_shared<Group>(Group{});
    g->set_transform(tf::scaling(2.0, 2.0, 2.0));

    auto s1 = std::make_shared<Sphere>(Sphere{});
    s1->set_transform(tf::translation(5.0, 0.0, 0.0));

    Group::add_child(g, s1);

    const auto r = Ray{make_point(10.0, 0.0, -10.0), make_vector(0.0, 0.0, 1.0)};
    const auto xs = g->intersect(r);
    EXPECT_EQ(xs.size(), 2);
}
