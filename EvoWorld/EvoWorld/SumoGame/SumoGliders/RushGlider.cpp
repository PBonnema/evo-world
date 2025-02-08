#include "RushGlider.h"
#include "../SumoGame.h"

#include <SFML/Graphics/CircleShape.hpp>

RushGlider::RushGlider(const Vector2<double>& position, const double mass, const double radius) :
    Glider{position, mass, radius}
{
    auto& circle = *dynamic_cast<sf::CircleShape*>(get_shape().get_drawables()[0].get());
    circle.setFillColor(sf::Color::Red);
}

Vector2<double> RushGlider::next_sumo_move(const SumoGame& sumo_game, const std::chrono::high_resolution_clock::time_point& now,
                                           const std::chrono::duration<double>& time_step) const
{
    if (sumo_game.get_participants().size() <= 1)
    {
        return {0.0, 0.0};
    }

    // Move full force to the nearest opponent
    Vector2<double> nearest_opponent_position;
    double nearest_distance_squared = std::numeric_limits<double>::infinity();
    for (const auto& participant : sumo_game.get_participants())
    {
        if (participant.get() == this)
        {
            continue;
        }

        const auto distance_squared = get_position().distance_squared(participant->get_position());
        if (distance_squared < nearest_distance_squared)
        {
            nearest_opponent_position = participant->get_position();
            nearest_distance_squared = distance_squared;
        }
    }

    const auto force = (nearest_opponent_position - get_position()).get_normalized() * sumo_game.get_max_acceleration() * mass_;
    return force;
}
