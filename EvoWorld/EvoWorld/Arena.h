#pragma once
#include "CompoundShape.h"

class Arena
{
public:
    explicit Arena(double radius);

    [[nodiscard]] double get_radius() const;
    [[nodiscard]] const CompoundShape& get_shape() const;
    [[nodiscard]] CompoundShape& get_shape();
private:
    double radius_;
    CompoundShape shape_; // Class invariant: radius of shape_ is equal to radius_
};
