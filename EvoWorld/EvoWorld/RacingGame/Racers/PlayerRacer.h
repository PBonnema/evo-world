#pragma once
#include "Racer.h"

#include <SFML/Graphics/RenderWindow.hpp>

class PlayerRacer final : public Racer
{
public:
    PlayerRacer(const Vector2<double>& position, double mass, double radius, const sf::WindowBase& window);

    Vector2<double> next_move(const RacingGame& game, const std::chrono::high_resolution_clock::time_point& now, const std::chrono::duration<double>& time_step) const override;

private:
    const sf::WindowBase& window_;
};
