#include "Glider.h"

#include <ranges>

#include "Creature.h"

Glider::Glider(const Vector2<double>& position, const double mass, const double radius) :
    position_{position},
    velocity_{0.0, 0.0},
    acceleration_{0.0, 0.0},
    mass_{mass},
    radius_{radius}
{
}

const Vector2<double>& Glider::get_position() const
{
    return position_;
}

const Vector2<double>& Glider::get_velocity() const
{
    return velocity_;
}

const Vector2<double>& Glider::get_acceleration() const
{
    return acceleration_;
}

double Glider::get_mass() const
{
    return mass_;
}

double Glider::get_radius() const
{
    return radius_;
}

void Glider::update_physics(const std::chrono::duration<double>& time_step)
{
    // Simple Euler integration
    velocity_ += acceleration_ * time_step.count();
    position_ += velocity_ * time_step.count();
}

void Glider::apply_impulse(const Vector2<double>& force, const std::chrono::duration<double>& time_step)
{
    acceleration_ = force * time_step.count() / mass_;
}

// Vector2<double> Glider::next_sumo_move(std::ranges::input_range auto&& all_gliders,
//                                        const double max_force_amplitude, const double friction_amplitude) const
// {
//     // Move full force to the nearest opponent
//     Vector2<double> nearest_opponent_position;
//     double nearest_opponent_distance = std::numeric_limits<double>::max();
//     for (const std::shared_ptr<const Glider>& other_glider : all_gliders)
//     {
//         if (other_glider.get() == this)
//         {
//             continue;
//         }
//
//         if (const double distance = (other_glider->get_position() - position_).get_length(); distance < nearest_opponent_distance)
//         {
//             nearest_opponent_distance = distance;
//             nearest_opponent_position = other_glider->get_position();
//         }
//     }
//
//     const Vector2<double> force = (nearest_opponent_position - position_).get_normalized() * max_force_amplitude;
//     return force;
// }
