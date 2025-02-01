#include "PlayerGlider.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Mouse.hpp>

PlayerGlider::PlayerGlider(const Vector2<double>& position, const double mass, const double radius, const sf::WindowBase& window) :
    Glider{position, mass, radius},
    window_{window}
{
    auto& circle = *dynamic_cast<sf::CircleShape*>(get_shape().get_drawables()[0].get());
    circle.setFillColor(sf::Color::Green);
}

Vector2<double> PlayerGlider::next_sumo_move(const std::vector<std::shared_ptr<Glider>>& all_gliders, const double max_acceleration,
                                             double coefficient_of_friction) const
{
    // Take mouse position as input
    const auto raw_mouse_position = sf::Mouse::getPosition(window_);
    const Vector2<double> mouse_position{static_cast<double>(raw_mouse_position.x), static_cast<double>(raw_mouse_position.y)};

    // Calculate the force vector towards the mouse position
    return (mouse_position - get_position()).get_normalized() * max_acceleration * get_mass();
}
