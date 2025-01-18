#pragma once
#include <chrono>
#include <ranges>
#include <unordered_map>

#include "fwd_decl.h"
#include "Vector2.h"

class Glider
{
public:
    // Glider() = default;
    Glider(const Vector2<double>& position, double mass, double radius);

    [[nodiscard]] const Vector2<double>& get_position() const;
    [[nodiscard]] const Vector2<double>& get_velocity() const;
    [[nodiscard]] const Vector2<double>& get_acceleration() const;
    [[nodiscard]] double get_mass() const;
    [[nodiscard]] double get_radius() const;
    void update_physics(const std::chrono::duration<double>& time_step);
    void apply_impulse(const Vector2<double>& force, const std::chrono::duration<double>& time_step);
    [[nodiscard]] Vector2<double> next_sumo_move(std::ranges::input_range auto&& all_gliders,
                                                 double max_force_amplitude, double friction_amplitude) const;

private:
    Vector2<double> position_;
    Vector2<double> velocity_;
    Vector2<double> acceleration_;
    double mass_;
    double radius_;
};

Vector2<double> Glider::next_sumo_move(std::ranges::input_range auto&& all_gliders, double max_force_amplitude,
    double friction_amplitude) const
{
    // Move full force to the nearest opponent
    Vector2<double> nearest_opponent_position;
    double nearest_opponent_distance = std::numeric_limits<double>::max();
    for (const std::shared_ptr<const Glider>& other_glider : all_gliders)
    {
        if (other_glider.get() == this)
        {
            continue;
        }

        if (const double distance = (other_glider->get_position() - position_).get_length(); distance < nearest_opponent_distance)
        {
            nearest_opponent_distance = distance;
            nearest_opponent_position = other_glider->get_position();
        }
    }

    const Vector2<double> force = (nearest_opponent_position - position_).get_normalized() * max_force_amplitude;
    return force;
}