#include <gtest/gtest.h>
#include <memory>

#include "Intersection.h"
#include "Ray.h"
#include "Sphere.h"
#include "Plane.h"
#include "util.h"

TEST(Intersection, Creation) {
    const auto sphere = std::make_shared<Sphere>(Sphere{});
    const auto intersection = Intersection{3.5, sphere};
    EXPECT_EQ(intersection.t, 3.5);
    EXPECT_TRUE(intersection.object);
    EXPECT_EQ(intersection.object, sphere);
}

TEST(Intersection, Aggregating) {
    const auto sphere = std::make_shared<Sphere>(Sphere{});
    const auto i1 = Intersection{1.0, sphere};
    const auto i2 = Intersection{2.0, sphere};
    const auto xs = Intersections{i1, i2};
    ASSERT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 1.0);
    EXPECT_EQ(xs[1].t, 2.0);
}

TEST(Intersection, HitNonNegative) {
    const auto sphere = std::make_shared<Sphere>(Sphere{});
    const auto i1 = Intersection{1.0, sphere};
    const auto i2 = Intersection{2.0, sphere};
    const auto xs = Intersections{i1, i2};
    const auto hit_maybe = hit(xs);
    EXPECT_TRUE(hit_maybe);
    EXPECT_EQ(*hit_maybe, i1);
}

TEST(Intersection, HitSomeNegative) {
    const auto sphere = std::make_shared<Sphere>(Sphere{});
    const auto i1 = Intersection{-1.0, sphere};
    const auto i2 = Intersection{1.0, sphere};
    const auto xs = Intersections{i2, i1};
    const auto hit_maybe = hit(xs);
    EXPECT_TRUE(hit_maybe);
    EXPECT_EQ(*hit_maybe, i2);
}

TEST(Intersection, HitAllNegative) {
    const auto sphere = std::make_shared<Sphere>(Sphere{});
    const auto i1 = Intersection{-2.0, sphere};
    const auto i2 = Intersection{-1.0, sphere};
    const auto xs = Intersections{i2, i1};
    const auto hit_maybe = hit(xs);
    EXPECT_FALSE(hit_maybe);
}

TEST(Intersection, HitLowestNonNegative) {
    const auto sphere = std::make_shared<Sphere>(Sphere{});
    const auto i1 = Intersection{5.0, sphere};
    const auto i2 = Intersection{7.0, sphere};
    const auto i3 = Intersection{-3.0, sphere};
    const auto i4 = Intersection{2.0, sphere};
    const auto xs = Intersections{i1, i2, i3, i4};
    const auto hit_maybe = hit(xs);
    EXPECT_TRUE(hit_maybe);
    EXPECT_EQ(*hit_maybe, i4);
}

TEST(Intersection, PrecomputingIntersectionState) {
    const auto r = Ray{make_point(0.0, 0.0, -5.0), make_vector(0.0, 0.0, 1.0)};
    const auto sphere = std::make_shared<Sphere>(Sphere{});
    const auto i = Intersection{4.0, sphere};
    const auto comps = i.prepare_computations(r);
    EXPECT_EQ(comps.t, i.t);
    EXPECT_EQ(comps.object, i.object);
    EXPECT_EQ(comps.point, make_point(0.0, 0.0, -1.0));
    EXPECT_EQ(comps.eyev, make_vector(0.0, 0.0, -1.0));
    EXPECT_EQ(comps.normalv, make_vector(0.0, 0.0, -1.0));
}

TEST(Intersection, HitIntersectionOutside) {
    const auto r = Ray{make_point(0.0, 0.0, -5.0), make_vector(0.0, 0.0, 1.0)};
    const auto sphere = std::make_shared<Sphere>(Sphere{});
    const auto i = Intersection{4.0, sphere};
    const auto comps = i.prepare_computations(r);
    EXPECT_FALSE(comps.inside);
}

TEST(Intersection, HitIntersectionInside) {
    const auto r = Ray{make_point(0.0, 0.0, 0.0), make_vector(0.0, 0.0, 1.0)};
    const auto sphere = std::make_shared<Sphere>(Sphere{});
    const auto i = Intersection{1.0, sphere};
    const auto comps = i.prepare_computations(r);
    EXPECT_EQ(comps.point, make_point(0.0, 0.0, 1.0));
    EXPECT_EQ(comps.eyev, make_vector(0.0, 0.0, -1.0));
    EXPECT_EQ(comps.normalv, make_vector(0.0, 0.0, -1.0));
    EXPECT_TRUE(comps.inside);
}

TEST(Intersection, HitShouldOffsetPoint) {
    const auto r = Ray{make_point(0.0, 0.0, -5.0), make_vector(0.0, 0.0, 1.0)};
    auto sphere = std::make_shared<Sphere>(Sphere{});
    sphere->set_transform(tf::translation(0.0, 0.0, 1.0));
    const auto i = Intersection{5.0, sphere};
    const auto comps = i.prepare_computations(r);
    EXPECT_LT(comps.over_point.z(), -EPSILON / 2.0);
    EXPECT_GT(comps.point.z(), comps.over_point.z());
}

TEST(Intersection, PrecomputingTheReflectionVector) {
    const auto plane = std::make_shared<Plane>(Plane{});

    const auto loc = std::sqrt(2.0) / 2.0;
    const auto r = Ray{make_point(0.0, 1.0, -1.0), make_vector(0.0, -loc, loc)};

    const auto i = Intersection{std::sqrt(2.0), plane};

    const auto comps = i.prepare_computations(r);
    EXPECT_EQ(comps.reflectv, make_vector(0.0, loc, loc));
}

TEST(Intersection, FindingN1AndN2AtVariousIntersections) {
    auto A = std::make_shared<Sphere>(make_glass_sphere());
    A->set_transform(tf::scaling(2.0, 2.0, 2.0));
    auto material_a = Material{};
    material_a.refractive_index = 1.5;
    A->set_material(material_a);

    auto B = std::make_shared<Sphere>(make_glass_sphere());
    B->set_transform(tf::translation(0.0, 0.0, -0.25));
    auto material_b = Material{};
    material_b.refractive_index = 2.0;
    B->set_material(material_b);

    auto C = std::make_shared<Sphere>(make_glass_sphere());
    C->set_transform(tf::translation(0.0, 0.0, 0.25));
    auto material_c = Material{};
    material_c.refractive_index = 2.5;
    C->set_material(material_c);

    const auto ray = Ray{make_point(0.0, 0.0, -4.0), make_vector(0.0, 0.0, 1.0)};
    const auto xs = Intersections{
            Intersection{2, A},
            Intersection{2.75, B},
            Intersection{3.25, C},
            Intersection{4.75, B},
            Intersection{5.25, C},
            Intersection{6, A}
    };

    std::vector<std::pair<double, double>> expected_ns{
            {1.0, 1.5},
            {1.5, 2.0},
            {2.0, 2.5},
            {2.5, 2.5},
            {2.5, 1.5},
            {1.5, 1.0}
    };

    for (size_t index = 0; index < expected_ns.size(); ++index) {
        const auto comps = xs[index].prepare_computations(ray, xs);
        EXPECT_EQ(comps.n1, expected_ns[index].first);
        EXPECT_EQ(comps.n2, expected_ns[index].second);
    }
}

TEST(Intersection, UnderPointIsOffsetBelowTheSurface) {
    const auto r = Ray{make_point(0.0, 1.0, -5.0), make_vector(0.0, 0.0, 1.0)};
    const auto sphere = std::make_shared<Sphere>(make_glass_sphere());
    sphere->set_transform(tf::translation(0.0, 0.0, 1.0));

    const auto i = Intersection{5.0, sphere};
    const auto xs = Intersections{i};

    const auto comps = i.prepare_computations(r, xs);
    EXPECT_GT(comps.under_point.z(), EPSILON / 2.0);
    EXPECT_LT(comps.point.z(), comps.under_point.z());
}

TEST(Intersection, SchlickApproximationUnderTotalInternalReflection) {
    const auto shape = std::make_shared<Sphere>(make_glass_sphere());
    const auto loc = std::sqrt(2.0) / 2.0;
    const auto ray = Ray{make_point(0.0, 0.0, loc), make_vector(0.0, 1.0, 0.0)};
    const auto xs = Intersections{Intersection{-loc, shape}, Intersection{loc, shape}};
    const auto comps = xs[1].prepare_computations(ray, xs);
    const auto reflectance = comps.schlick();
    EXPECT_EQ(reflectance, 1.0);
}

TEST(Intersection, SchlickApproximationWithPerpendicularViewingAngle) {
    const auto shape = std::make_shared<Sphere>(make_glass_sphere());
    const auto ray = Ray{make_point(0.0, 0.0, 0.0), make_vector(0.0, 1.0, 0.0)};
    const auto xs = Intersections{Intersection{-1.0, shape}, Intersection{1.0, shape}};
    const auto comps = xs[1].prepare_computations(ray, xs);
    const auto reflectance = comps.schlick();
    EXPECT_TRUE(within_epsilon(reflectance, 0.04));
}

TEST(Intersection, SchlickApproximationWithSmallAngleAndN2GreaterThanN1) {
    const auto shape = std::make_shared<Sphere>(make_glass_sphere());
    const auto ray = Ray{make_point(0.0, 0.99, -2.0), make_vector(0.0, 0.0, 1.0)};
    const auto xs = Intersections{Intersection{1.8589, shape}};
    const auto comps = xs[0].prepare_computations(ray, xs);
    const auto reflectance = comps.schlick();
    EXPECT_TRUE(within_epsilon(reflectance, 0.48873));
}
