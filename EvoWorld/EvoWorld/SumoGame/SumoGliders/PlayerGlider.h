#pragma once
#include "Glider.h"
#include "../../fwd_decl.h"

#include <SFML/Graphics/RenderWindow.hpp>

class PlayerGlider final : public Glider
{
public:
    PlayerGlider(const Vector2<double>& position, double mass, double radius, const sf::WindowBase& window);

    Vector2<double> next_sumo_move(const SumoGame& sumo_game, const std::chrono::high_resolution_clock::time_point& now, const std::chrono::duration<double>& time_step) const override;

private:
    const sf::WindowBase& window_;
};
