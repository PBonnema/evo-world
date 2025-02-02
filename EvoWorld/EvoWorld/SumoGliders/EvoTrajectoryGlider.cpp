#include "EvoTrajectoryGlider.h"
#include "../SumoGame.h"

EvoTrajectoryGlider::EvoTrajectoryGlider(const Vector2<double>& position, const double mass, const double radius, trajectory_t trajectory) :
    Glider{position, mass, radius},
    trajectory_{std::move(trajectory)}
{
}

Vector2<double> EvoTrajectoryGlider::next_sumo_move(const SumoGame& sumo_game, const std::chrono::high_resolution_clock::time_point& now, const std::chrono::duration<double>& time_step) const
{
    start_time_ = start_time_.value_or(now);

    // Find the nearest opponent
    std::shared_ptr<Glider> nearest_opponent;
    auto nearest_distance_squared = std::numeric_limits<double>::infinity();
    for (const auto& participant : sumo_game.get_participants())
    {
        if (participant.get() == this)
        {
            continue;
        }

        const auto distance_squared = get_position().distance_squared(participant->get_position());
        if (distance_squared < nearest_distance_squared)
        {
            nearest_opponent = participant;
            nearest_distance_squared = distance_squared;
        }
    }
    const auto target_position = nearest_opponent->get_position();
    const auto angle_to_target = (target_position - get_position()).get_angle();

    // Find the acceleration vector for the current time
    const auto elapsed_time = now - start_time_.value();
    auto trajectory_time_sum = std::chrono::duration<double>::zero();
    for (const auto& [duration, acceleration] : trajectory_)
    {
        trajectory_time_sum += duration;
        if (trajectory_time_sum > elapsed_time)
        {
            // Rotate the acceleration vector to point towards the target
            return acceleration.get_rotated(angle_to_target);
        }
    }

    // If we reached the end of the trajectory, restart
    start_time_ = now;

    return trajectory_[0].acceleration.get_rotated(angle_to_target);
}
