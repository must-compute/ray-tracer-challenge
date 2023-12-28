#ifndef RAY_TRACER_CHALLENGE_CSG_H
#define RAY_TRACER_CHALLENGE_CSG_H

#include <memory>

#include "Shape.h"
#include "Tuple.h"
#include "BoundingBox.h"

class Ray;

class Intersection;

enum class CSGOperation {
    Invalid, Union, Intersection, Difference,
};

class CSG final : public Shape, public std::enable_shared_from_this<CSG> {
private:
    // Make the constructor private so users are forced to create a shared_ptr to prevent enable_shared_from_this misuse.
    CSG(CSGOperation operation, std::shared_ptr<Shape> left, std::shared_ptr<Shape> right) : operation_{operation},
                                                                                             left_{std::move(left)},
                                                                                             right_{std::move(right)} {}

public:
    static std::shared_ptr<CSG> make_csg(CSGOperation operation,
                                         std::shared_ptr<Shape> left,
                                         std::shared_ptr<Shape> right);

    [[nodiscard]] static bool intersection_allowed(CSGOperation op, bool left_hit, bool inside_left, bool inside_right);

    bool operator==(const CSG &other) const = delete;

    [[nodiscard]] Intersections local_intersect(const Ray &ray) override;

    [[nodiscard]] Tuple local_normal_at(const Tuple &point_in_object_space,
                                        const std::optional<Intersection> &intersection) const override;

    [[nodiscard]] BoundingBox make_bounding_box() const override;

    [[nodiscard]] CSGOperation operation() const;

    [[nodiscard]] std::shared_ptr<Shape> left() const;

    [[nodiscard]] std::shared_ptr<Shape> right() const;

private:
    CSGOperation operation_{CSGOperation::Invalid};
    // TODO these shared_ptrs can probably just be unique_ptrs
    std::shared_ptr<Shape> left_{};
    std::shared_ptr<Shape> right_{};
};


#endif //RAY_TRACER_CHALLENGE_CSG_H
