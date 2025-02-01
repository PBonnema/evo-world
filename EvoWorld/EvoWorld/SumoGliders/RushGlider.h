#pragma once
#include "Glider.h"

class RushGlider final : public Glider
{
public:
    RushGlider(const Vector2<double>& position, double mass, double radius);

    Vector2<double> next_sumo_move(const std::vector<std::shared_ptr<Glider>>& all_gliders, double max_acceleration,
                                   double coefficient_of_friction) const override;
};
