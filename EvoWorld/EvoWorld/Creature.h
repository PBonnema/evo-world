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
    [[nodiscard]] const position& get_position() const;
    void set_position(const position& position);

    void move(const Vector2<double>& displacement);

private:
    position position_;
    CompoundShape shape_; // Class invariant: position of shape_ is equal to position_
};
