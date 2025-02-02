#include "PlayerGlider.h"
#include "../SumoGame.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Mouse.hpp>

PlayerGlider::PlayerGlider(const Vector2<double>& position, const double mass, const double radius, const sf::WindowBase& window) :
    Glider{position, mass, radius},
    window_{window}
{
    auto& circle = *dynamic_cast<sf::CircleShape*>(get_shape().get_drawables()[0].get());
    circle.setFillColor(sf::Color::Green);
}

Vector2<double> PlayerGlider::next_sumo_move(const SumoGame& sumo_game, const std::chrono::high_resolution_clock::time_point& now, const std::chrono::duration<double>& time_step) const
{
    // Take mouse position as input
    const auto raw_mouse_position = sf::Mouse::getPosition(window_);
    const Vector2<double> mouse_position{static_cast<double>(raw_mouse_position.x), static_cast<double>(raw_mouse_position.y)};

    // Calculate the force vector towards the mouse position
    return (mouse_position - get_position()).get_normalized() * sumo_game.get_max_acceleration() * mass_;
}
