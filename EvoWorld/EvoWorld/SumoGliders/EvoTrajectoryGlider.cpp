#include "EvoTrajectoryGlider.h"

EvoTrajectoryGlider::EvoTrajectoryGlider(const Vector2<double>& position, const double mass, const double radius) :
    Glider{position, mass, radius}
{
}

Vector2<double> EvoTrajectoryGlider::next_sumo_move(const SumoGame& sumo_game, const std::chrono::high_resolution_clock::time_point& now, const std::chrono::duration<double>& time_step) const
{
    start_time_ = start_time_.value_or(now);




    return {};
}
