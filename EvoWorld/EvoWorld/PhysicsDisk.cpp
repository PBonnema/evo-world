#include "PhysicsDisk.h"

PhysicsDisk::PhysicsDisk(const Vector2<double>& position, const double mass, const double radius) :
    position_{position},
    velocity_{0.0, 0.0},
    mass_{mass},
    radius_{radius}
{
}

const Vector2<double>& PhysicsDisk::get_position() const
{
    return position_;
}

const Vector2<double>& PhysicsDisk::get_velocity() const
{
    return velocity_;
}

double PhysicsDisk::get_mass() const
{
    return mass_;
}

double PhysicsDisk::get_radius() const
{
    return radius_;
}

void PhysicsDisk::set_position(const Vector2<double>& position)
{
    position_ = position;
    on_position_changed(position_);
}

void PhysicsDisk::add_position(const Vector2<double>& displacement)
{
    position_ += displacement;
    on_position_changed(position_);
}

void PhysicsDisk::add_velocity(const Vector2<double>& velocity)
{
    velocity_ += velocity;
}

void PhysicsDisk::apply_impulse(const Vector2<double>& force, const std::chrono::duration<double>& time_step)
{
    const auto acceleration = force / mass_;

    // Simple Euler integration
    velocity_ += acceleration * time_step.count();
    add_position(velocity_ * time_step.count());
}
