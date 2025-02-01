#include "RushGlider.h"

#include <SFML/Graphics/CircleShape.hpp>

RushGlider::RushGlider(const Vector2<double>& position, double mass, double radius) :
    Glider{position, mass, radius}
{
    auto& circle = *dynamic_cast<sf::CircleShape*>(get_shape().get_drawables()[0].get());
    circle.setFillColor(sf::Color::Red);
}

Vector2<double> RushGlider::next_sumo_move(const std::vector<std::shared_ptr<Glider>>& all_gliders, double max_acceleration,
    double coefficient_of_friction) const
{
    // Move full force to the nearest opponent
    Vector2<double> nearest_opponent_position;
    auto nearest_opponent_distance = std::numeric_limits<double>::max();
    for (const auto& other_glider : all_gliders)
    {
        if (other_glider.get() == this)
        {
            continue;
        }

        const auto distance = (other_glider->get_position() - get_position()).get_length();
        if (distance < nearest_opponent_distance)
        {
            nearest_opponent_distance = distance;
            nearest_opponent_position = other_glider->get_position();
        }
    }

    const auto force = (nearest_opponent_position - get_position()).get_normalized() * max_acceleration * mass_;
    return force;
}
