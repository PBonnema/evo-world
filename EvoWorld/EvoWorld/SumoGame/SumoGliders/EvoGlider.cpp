#include "EvoGlider.h"
#include "../SumoGame.h"

#include <numbers>
#include <SFML/Graphics/CircleShape.hpp>

EvoGlider::EvoGlider(const Vector2<double>& position, const double mass, const double radius) :
    Glider{position, mass, radius}
{
    auto& circle = *dynamic_cast<sf::CircleShape*>(get_shape().get_drawables()[0].get());
    circle.setFillColor(sf::Color::Cyan);
}

Vector2<double> EvoGlider::next_sumo_move(const SumoGame& sumo_game, const std::chrono::high_resolution_clock::time_point& now,
    const std::chrono::duration<double>& time_step) const
{
    // if (sumo_game.get_participants().size() <= 1)
    // {
        return {0.0, 0.0};
    // }

    // const auto target = sumo_game.get_participants().front();
    // const auto& arena = sumo_game.get_arena();
    //
    // const auto polar_position = (get_position() - arena.get_center()).to_polar();
    // const auto polar_velocity = get_velocity().to_polar();
    // const auto polar_opponent_position = (target->get_position() - arena.get_center()).to_polar();
    // const auto polar_opponent_velocity = target->get_velocity().to_polar();
    //
    // return forces_[
    //     polar_position.x() / (std::numbers::pi*2 / number_of_forces_per_parameters),
    //     polar_position.y() / (arena.get_radius() / number_of_forces_per_parameters),
    //     polar_velocity.x() / (std::numbers::pi*2 / number_of_forces_per_parameters),
    //     polar_velocity.y() / (arena.get_radius() / number_of_forces_per_parameters),
    //     polar_opponent_position.x() / (std::numbers::pi*2 / number_of_forces_per_parameters),
    //     polar_opponent_position.y() / (arena.get_radius() / number_of_forces_per_parameters),
    //     polar_opponent_velocity.x() / (std::numbers::pi*2 / number_of_forces_per_parameters),
    //     polar_opponent_velocity.y() / (arena.get_radius() / number_of_forces_per_parameters)
    // ];
}
