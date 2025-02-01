#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "Glider.h"

class PlayerGlider final : public Glider
{
public:
    PlayerGlider(const Vector2<double>& position, double mass, double radius, const sf::WindowBase& window);

    Vector2<double> next_sumo_move(const std::vector<std::shared_ptr<Glider>>& all_gliders, double max_acceleration,
                                   double coefficient_of_friction) const override;

private:
    const sf::WindowBase& window_;
};
