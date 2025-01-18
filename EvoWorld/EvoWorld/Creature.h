#pragma once
#include "Vector2.h"
#include "CompoundShape.h"

class Creature
{
public:
    typedef Vector2<double> position;

    explicit Creature(const position& position);

    [[nodiscard]] const CompoundShape& get_shape() const;
    [[nodiscard]] CompoundShape& get_shape();

private:
    position position_;
    CompoundShape shape_; // Class invariant: position of shape_ is equal to position_
};
