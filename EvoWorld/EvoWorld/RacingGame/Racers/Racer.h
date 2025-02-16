#pragma once
#include "../../CompoundShape.h"
#include "../../Vector2.h"
#include "../../PhysicsDisk.h"
#include "../fwd_decl.h"

#include <chrono>

class Racer : public PhysicsDisk
{
public:
    Racer(const Vector2<double>& position, double mass, double radius);
    ~Racer() override = default;

    [[nodiscard]] const CompoundShape& get_shape() const;
    [[nodiscard]] CompoundShape& get_shape();
    [[nodiscard]] virtual Vector2<double> next_move(const RacingGame& game, const std::chrono::high_resolution_clock::time_point& now, const std::chrono::duration<double>& time_step) const = 0;

protected:
    void on_position_changed(const Vector2<double>& position) override;

private:
    CompoundShape shape_; // Class invariant: position of shape_ is equal to position_. It is the center of shape_
};
