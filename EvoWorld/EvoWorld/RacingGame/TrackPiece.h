#pragma once
#include "../CompoundShape.h"
#include "../PhysicsStaticRectangle.h"

class TrackPiece : public PhysicsStaticRectangle
{
public:
    explicit TrackPiece(const Vector2<double>& top_left, const Vector2<double>& dimensions, double orientation_radians);

    [[nodiscard]] const CompoundShape& get_shape() const;

private:
    CompoundShape shape_; // Class invariant: radius of shape_ is equal to radius_
};
