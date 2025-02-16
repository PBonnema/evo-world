#pragma once
#include "Vector2.h"
#include "fwd_decl.h"

class PhysicsStaticRectangle
{
public:
    PhysicsStaticRectangle(const Vector2<double>& top_left, const Vector2<double>& dimensions, double orientation_radians);

    [[nodiscard]] const Vector2<double>& get_top_left() const;
    [[nodiscard]] Vector2<double> get_dimensions() const;
    [[nodiscard]] Vector2<double> get_closest_point(const Vector2<double>& point) const;
    [[nodiscard]] bool overlaps(const PhysicsDisk& disk) const;

private:
    Vector2<double> top_left_;
    const Vector2<double> dimensions_;
    const double orientation_radians_;
};
