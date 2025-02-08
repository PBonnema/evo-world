#include "CenteringGlider.h"
#include "../SumoGame.h"

#include <SFML/Graphics/CircleShape.hpp>

CenteringGlider::CenteringGlider(const Vector2<double>& position, const double mass, const double radius) :
    Glider{position, mass, radius}
{
    auto& circle = *dynamic_cast<sf::CircleShape*>(get_shape().get_drawables()[0].get());
    circle.setFillColor(sf::Color::Yellow);
}

Vector2<double> CenteringGlider::next_sumo_move(const SumoGame& sumo_game, const std::chrono::high_resolution_clock::time_point& now, const std::chrono::duration<double>& time_step) const
{
    // Move full force to the center of the arena
    const auto force = (sumo_game.get_arena().get_center() - get_position()).get_normalized() * sumo_game.get_max_acceleration() * get_mass();
    return force;
}
