#pragma once
#include "RacingTrack.h"
#include "Racers/fwd_decl.h"

#include <chrono>
#include <random>

class RacingGame
{
public:
    explicit RacingGame(const std::mt19937& random_generator, RacingTrack racing_track, double max_acceleration,
                      double coefficient_of_friction, const std::vector<std::shared_ptr<Racer>>& participants);

    [[nodiscard]] const RacingTrack& get_racing_track() const;
    [[nodiscard]] const std::vector<std::shared_ptr<Racer>>& get_participants() const;
    [[nodiscard]] double get_max_acceleration() const;
    [[nodiscard]] double get_coefficient_of_friction() const;
    void update(const std::chrono::high_resolution_clock::time_point& now, const std::chrono::duration<double>& time_step) const;

private:
    const double max_acceleration_;
    const double coefficient_of_friction_;

    RacingTrack racing_track_;
    std::vector<std::shared_ptr<Racer>> participants_;
    mutable std::mt19937 random_generator_;
};
