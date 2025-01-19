#include "Glider.h"
#include "Creature.h"

Glider::Glider(const Vector2<double>& position, const double mass, const double radius) :
    position_{position},
    velocity_{0.0, 0.0},
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

double Glider::get_mass() const
{
    return mass_;
}

double Glider::get_radius() const
{
    return radius_;
}

void Glider::apply_impulse(const Vector2<double>& force, const std::chrono::duration<double>& time_step)
{
    const auto acceleration = force / mass_;

    // Simple Euler integration
    velocity_ += acceleration * time_step.count();
    position_ += velocity_ * time_step.count();
}
