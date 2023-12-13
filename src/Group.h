#ifndef RAY_TRACER_CHALLENGE_GROUP_H
#define RAY_TRACER_CHALLENGE_GROUP_H

#include <vector>
#include <memory>

#include "Shape.h"

class Group final : public Shape {
public:

    bool operator==(const Group &other) const = default;

    [[nodiscard]] std::vector<std::shared_ptr<Shape>> children() const;

    static void add_child(const std::shared_ptr<Group> &group, const std::shared_ptr<Shape> &child);

    [[nodiscard]] Intersections local_intersect(const Ray &ray) override;

    [[nodiscard]] Tuple local_normal_at(const Tuple &point_in_object_space) const override;

private:
    std::vector<std::shared_ptr<Shape>> children_;
};


#endif //RAY_TRACER_CHALLENGE_GROUP_H
