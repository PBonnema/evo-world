#include "Glider.h"

#include <SFML/Graphics/CircleShape.hpp>

Glider::Glider(const Vector2<double>& position, const double mass, const double radius) :
    shape_{{std::make_shared<sf::CircleShape>(static_cast<float>(radius))}},
    position_{position},
    velocity_{0.0, 0.0},
    mass_{mass},
    radius_{radius}
{
    auto& circle = *dynamic_cast<sf::CircleShape*>(shape_.get_drawables()[0].get());
    circle.setFillColor(sf::Color::Red);

    shape_.setOrigin(sf::Vector2f{static_cast<float>(radius), static_cast<float>(radius)});
    shape_.setPosition({static_cast<float>(position_.get_x()), static_cast<float>(position_.get_y())});
}

const CompoundShape& Glider::get_shape() const
{
    return shape_;
}

CompoundShape& Glider::get_shape()
{
    return shape_;
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

void Glider::add_position(const Vector2<double>& position)
{
    position_ += position;
    shape_.setPosition({static_cast<float>(position_.get_x()), static_cast<float>(position_.get_y())});
}

void Glider::add_velocity(const Vector2<double>& velocity)
{
    velocity_ += velocity;
}

void Glider::apply_impulse(const Vector2<double>& force, const std::chrono::duration<double>& time_step)
{
    const auto acceleration = force / mass_;

    // Simple Euler integration
    velocity_ += acceleration * time_step.count();
    position_ += velocity_ * time_step.count();
    shape_.setPosition({static_cast<float>(position_.get_x()), static_cast<float>(position_.get_y())});
}
