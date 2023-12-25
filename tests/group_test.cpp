
#include <gtest/gtest.h>

#include <numbers>
#include <memory>

#include "Cylinder.h"
#include "Group.h"
#include "Sphere.h"
#include "Transformations.h"
#include "TestShape.h"
#include "StripePattern.h"

TEST(Group, CreateNewGroup) {
    const auto g = Group::make_group();
    EXPECT_EQ(g->transform(), tf::Transform::identity());
    EXPECT_EQ(g->children().size(), 0);
}

TEST(Group, AddingChildToGroup) {
    auto g = Group::make_group();
    const auto s = std::make_shared<TestShape>(TestShape{});
    ASSERT_EQ(g->children().size(), 0);
    g->add_child(s);
    ASSERT_EQ(g->children().size(), 1);
    EXPECT_EQ(g->children()[0], s);
    ASSERT_TRUE(s->parent());
    EXPECT_EQ(*s->parent(), *g);
}

TEST(Group, IntersectingRayWithEmptyGroup) {
    auto g = Group::make_group();
    const auto r = Ray{make_point(0.0, 0.0, 0.0), make_vector(0.0, 0.0, 1.0)};
    EXPECT_EQ(g->local_intersect(r).size(), 0);
}

TEST(Group, IntersectingRayWithNonEmptyGroup) {
    auto g = Group::make_group();
    auto s1 = std::make_shared<Sphere>(Sphere{});
    auto s2 = std::make_shared<Sphere>(Sphere{});
    auto s3 = std::make_shared<Sphere>(Sphere{});
    s2->set_transform(tf::translation(0.0, 0.0, -3.0));
    s3->set_transform(tf::translation(5.0, 0.0, 0.0));
    g->add_child(s1);
    g->add_child(s2);
    g->add_child(s3);

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
    auto g = Group::make_group();
    g->set_transform(tf::scaling(2.0, 2.0, 2.0));

    auto s1 = std::make_shared<Sphere>(Sphere{});
    s1->set_transform(tf::translation(5.0, 0.0, 0.0));

    g->add_child(s1);

    const auto r = Ray{make_point(10.0, 0.0, -10.0), make_vector(0.0, 0.0, 1.0)};
    const auto xs = g->intersect(r);
    EXPECT_EQ(xs.size(), 2);
}

TEST(Group, ConvertingPointToWorldSpaceToObjectSpace) {
    auto g1 = Group::make_group();
    g1->set_transform(tf::rotation_y(std::numbers::pi / 2));
    auto g2 = Group::make_group();
    g2->set_transform(tf::scaling(2.0, 2.0, 2.0));
    g1->add_child(g2);

    auto s = std::make_shared<Sphere>(Sphere{});
    s->set_transform(tf::translation(5.0, 0.0, 0.0));
    g2->add_child(s);

    EXPECT_EQ(s->world_to_object(make_point(-2.0, 0.0, -10.0)), make_point(0.0, 0.0, -1.0));
}

TEST(Group, ConvertingNormalFromObjectSpaceToWorldSpace) {
    auto g1 = Group::make_group();
    g1->set_transform(tf::rotation_y(std::numbers::pi / 2));
    auto g2 = Group::make_group();
    g2->set_transform(tf::scaling(1.0, 2.0, 3.0));
    g1->add_child(g2);

    auto s = std::make_shared<Sphere>(Sphere{});
    s->set_transform(tf::translation(5.0, 0.0, 0.0));
    g2->add_child(s);

    const auto loc = std::sqrt(3.0) / 3.0;
    EXPECT_EQ(s->normal_to_world(make_vector(loc, loc, loc)), make_vector(0.2857, 0.4286, -0.8571));
}


TEST(Group, FindingTheNormalOnAChildObject) {
    auto g1 = Group::make_group();
    g1->set_transform(tf::rotation_y(std::numbers::pi / 2));
    auto g2 = Group::make_group();
    g2->set_transform(tf::scaling(1.0, 2.0, 3.0));
    g1->add_child(g2);

    auto s = std::make_shared<Sphere>(Sphere{});
    s->set_transform(tf::translation(5.0, 0.0, 0.0));
    g2->add_child(s);

    EXPECT_EQ(s->normal_at(make_point(1.7321, 1.1547, -5.5774)), make_vector(0.2857, 0.4286, -0.8571));
}

TEST(Group, StripesPatternWithGroupTransformation) {
    const auto white = make_color(1.0, 1.0, 1.0);
    const auto black = make_color(0.0, 0.0, 0.0);

    auto g1 = Group::make_group();
    g1->set_transform(tf::translation(0.3, 0.0, 0.0));
    auto g2 = Group::make_group();
    g2->set_transform(tf::translation(0.4, 0.0, 0.0));
    g1->add_child(g2);

    auto s = std::make_shared<Sphere>(Sphere{});
    s->set_transform(tf::translation(0.3, 0.0, 0.0));
    g2->add_child(s);

    // All the transforms (parent groups, and the shape itself, and the pattern itself) should add up to x being offset by 1.1.
    auto pattern = StripePattern{white, black};
    pattern.set_transform(tf::translation(0.1, 0.1, 0.1));

    // That means we expect the pattern to transition at 0.1, 1.1, 2.1, etc.
    EXPECT_EQ(pattern.pattern_at_shape(*s, make_point(0.0999, 0.0, 0.0)), white);
    EXPECT_EQ(pattern.pattern_at_shape(*s, make_point(0.1001, 0.0, 0.0)), black);
    EXPECT_EQ(pattern.pattern_at_shape(*s, make_point(1.0999, 0.0, 0.0)), black);
    EXPECT_EQ(pattern.pattern_at_shape(*s, make_point(1.1001, 0.0, 0.0)), white);
    EXPECT_EQ(pattern.pattern_at_shape(*s, make_point(2.0999, 0.0, 0.0)), white);
    EXPECT_EQ(pattern.pattern_at_shape(*s, make_point(2.1001, 0.0, 0.0)), black);
}

TEST(Group, RayDoesNotIntersectChildrenIfBoundingBoxIsMissed) {
    const auto child = std::make_shared<TestShape>(TestShape{});
    auto group = Group::make_group();
    group->add_child(child);
    const auto ray = Ray{make_point(0.0, 0.0, -5.0), make_vector(0.0, 1.0, 0.0)};
    auto xs = group->intersect(ray);
    EXPECT_FALSE(child->local_ray());
}

TEST(Group, RayIntersectsChildrenIfBoundingBoxIsHit) {
    const auto child = std::make_shared<TestShape>(TestShape{});
    auto group = Group::make_group();
    group->add_child(child);
    const auto ray = Ray{make_point(0.0, 0.0, -5.0), make_vector(0.0, 0.0, 1.0)};
    auto xs = group->intersect(ray);
    EXPECT_TRUE(child->local_ray());
}
