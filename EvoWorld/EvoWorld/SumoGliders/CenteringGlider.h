#pragma once
#include "Glider.h"
#include "../fwd_decl.h"

class CenteringGlider final : public Glider
{
public:
    CenteringGlider(const Vector2<double>& position, double mass, double radius);

    Vector2<double> next_sumo_move(const SumoGame& sumo_game) const override;
};
