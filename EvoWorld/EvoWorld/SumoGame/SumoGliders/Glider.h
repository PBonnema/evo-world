#pragma once
#include "../../CompoundShape.h"
#include "../../Vector2.h"
#include "../../PhysicsDisk.h"
#include "../../fwd_decl.h"

#include <chrono>

class Glider : public PhysicsDisk
{
public:
    Glider(const Vector2<double>& position, double mass, double radius);
    virtual ~Glider() = default;

    [[nodiscard]] const CompoundShape& get_shape() const;
    [[nodiscard]] CompoundShape& get_shape();
    [[nodiscard]] const Vector2<double>& get_position() const;
    [[nodiscard]] const Vector2<double>& get_velocity() const;
    [[nodiscard]] double get_mass() const;
    [[nodiscard]] double get_radius() const;
    void set_position(const Vector2<double>& position);
    void add_position(const Vector2<double>& position);
    void add_velocity(const Vector2<double>& velocity);
    void apply_impulse(const Vector2<double>& force, const std::chrono::duration<double>& time_step);
    [[nodiscard]] virtual Vector2<double> next_sumo_move(const SumoGame& sumo_game, const std::chrono::high_resolution_clock::time_point& now, const std::chrono::duration<double>& time_step) const = 0;

protected:
    const double mass_;
    const double radius_;

private:
    CompoundShape shape_; // Class invariant: position of shape_ is equal to position_. It is the center of shape_
    Vector2<double> position_;
    Vector2<double> velocity_;
};
