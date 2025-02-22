#pragma once
#include "Glider.h"

class CenteringGlider final : public Glider
{
public:
    CenteringGlider(const Vector2<double>& position, double mass, double radius);

    Vector2<double> next_sumo_move(const SumoGame& sumo_game, const std::chrono::high_resolution_clock::time_point& now, const std::chrono::duration<double>& time_step) const override;
};
