#ifndef RAY_TRACER_CHALLENGE_GROUP_H
#define RAY_TRACER_CHALLENGE_GROUP_H

#include <vector>
#include <memory>

#include "Shape.h"

class Bounds;

class Group final : public Shape, public std::enable_shared_from_this<Group> {
private:
    Group() = default;

public:
    static std::shared_ptr<Group> make_group();

    bool operator==(const Group &other) const = delete;

    [[nodiscard]] std::vector<std::shared_ptr<Shape>> children() const;

    void add_child(const std::shared_ptr<Shape> &child);

    [[nodiscard]] Intersections local_intersect(const Ray &ray) override;

    [[nodiscard]] Tuple local_normal_at(const Tuple &point_in_object_space) const override;

    [[nodiscard]] Bounds make_bounds() const override;

private:
    std::vector<std::shared_ptr<Shape>> children_;
};


#endif //RAY_TRACER_CHALLENGE_GROUP_H
