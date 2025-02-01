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
    [[nodiscard]] Vector2<double> next_sumo_move(std::ranges::view auto&& all_gliders, double max_force_magnitude,
                                                 double coefficient_of_friction) const
        requires std::is_same_v<std::add_pointer_t<std::add_const_t<std::remove_pointer_t<std::ranges::range_value_t<decltype(all_gliders
                                )>>>>, const Glider*>;

private:
    CompoundShape shape_; // Class invariant: position of shape_ is equal to position_
    Vector2<double> position_;
    Vector2<double> velocity_;
    double mass_;
    double radius_;
};

Vector2<double> Glider::next_sumo_move(std::ranges::view auto&& all_gliders, double max_force_magnitude,
                                       double coefficient_of_friction) const
    requires std::is_same_v<std::add_pointer_t<std::add_const_t<std::remove_pointer_t<std::ranges::range_value_t<decltype(all_gliders)>>>>,
                            const Glider*>
{
    // Move full force to the nearest opponent
    Vector2<double> nearest_opponent_position;
    auto nearest_opponent_distance = std::numeric_limits<double>::max();
    for (const auto other_glider : all_gliders)
    {
        if (other_glider == this)
        {
            continue;
        }

        const auto distance = (other_glider->get_position() - position_).get_length();
        if (distance < nearest_opponent_distance)
        {
            nearest_opponent_distance = distance;
            nearest_opponent_position = other_glider->get_position();
        }
    }

    const auto force = (nearest_opponent_position - position_).get_normalized() * max_force_magnitude;
    return force;
}
