#pragma once
#include "Glider.h"
#include "../fwd_decl.h"

class RushGlider final : public Glider
{
public:
    RushGlider(const Vector2<double>& position, double mass, double radius);

    Vector2<double> next_sumo_move(const SumoGame& sumo_game) const override;
};
