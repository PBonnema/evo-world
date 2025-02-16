#include "PlayerGlider.h"
#include "../SumoGame.h"
#include "../../Vector2_SfVector2f_conversions.h"

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
    const auto mouse_position = to_vector2<double>(sf::Mouse::getPosition(window_));

    // Calculate the force vector towards the mouse position
    return (mouse_position - get_position()).get_normalized() * sumo_game.get_max_acceleration() * mass_;
}
