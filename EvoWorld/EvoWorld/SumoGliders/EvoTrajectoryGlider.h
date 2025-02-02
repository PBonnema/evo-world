#pragma once
#include "Glider.h"
#include "../fwd_decl.h"

struct TrajectoryPoint
{
    std::chrono::duration<double> duration;
    Vector2<double> acceleration;
};

class EvoTrajectoryGlider final : public Glider
{
public:
    using trajectory_t = std::vector<TrajectoryPoint>;

    EvoTrajectoryGlider(const Vector2<double>& position, double mass, double radius, trajectory_t trajectory);

    Vector2<double> next_sumo_move(const SumoGame& sumo_game, const std::chrono::high_resolution_clock::time_point& now, const std::chrono::duration<double>& time_step) const override;

private:
    const trajectory_t trajectory_;
    mutable long long current_trajectory_index_ = 0;
    mutable std::optional<std::chrono::high_resolution_clock::time_point> start_time_;
};
