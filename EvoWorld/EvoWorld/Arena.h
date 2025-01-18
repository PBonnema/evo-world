#pragma once
#include "CompoundShape.h"
#include "Creature.h"
#include "Glider.h"

class Arena
{
public:
    explicit Arena(const Vector2<double>& midpoint, double radius);

    [[nodiscard]] constexpr Vector2<double> get_midpoint() const;
    [[nodiscard]] constexpr double get_radius() const;
    [[nodiscard]] const CompoundShape& get_shape() const;
    [[nodiscard]] CompoundShape& get_shape();
    [[nodiscard]] bool contains(const Vector2<double>& point) const;

private:
    Vector2<double> midpoint_;
    double radius_;
    CompoundShape shape_; // Class invariant: radius of shape_ is equal to radius_
};

constexpr Vector2<double> Arena::get_midpoint() const
{
    return midpoint_;
}

constexpr double Arena::get_radius() const
{
    return radius_;
}
