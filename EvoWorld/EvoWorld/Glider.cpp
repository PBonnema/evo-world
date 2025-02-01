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

Vector2<double> Glider::next_sumo_move(const std::vector<std::shared_ptr<Glider>>& all_gliders, const double max_acceleration,
    const double coefficient_of_friction) const
{
    // return {};
    // Move full force to the nearest opponent
    Vector2<double> nearest_opponent_position;
    auto nearest_opponent_distance = std::numeric_limits<double>::max();
    for (const auto& other_glider : all_gliders)
    {
        if (other_glider.get() == this)
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

    const auto force = (nearest_opponent_position - position_).get_normalized() * max_acceleration * mass_;
    return force;
}
