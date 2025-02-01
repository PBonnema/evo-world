#pragma once
#include "CompoundShape.h"
#include "Vector2.h"
#include <chrono>

class Glider
{
public:
    Glider(const Vector2<double>& position, double mass, double radius);

    [[nodiscard]] const CompoundShape& get_shape() const;
    [[nodiscard]] CompoundShape& get_shape();
    [[nodiscard]] const Vector2<double>& get_position() const;
    [[nodiscard]] const Vector2<double>& get_velocity() const;
    [[nodiscard]] double get_mass() const;
    [[nodiscard]] double get_radius() const;
    void apply_impulse(const Vector2<double>& force, const std::chrono::duration<double>& time_step);
    [[nodiscard]] Vector2<double> next_sumo_move(const std::vector<std::shared_ptr<Glider>>& all_gliders, double max_force_magnitude,
                                                 double coefficient_of_friction) const;

private:
    CompoundShape shape_; // Class invariant: position of shape_ is equal to position_
    Vector2<double> position_;
    Vector2<double> velocity_;
    double mass_;
    double radius_;
};
