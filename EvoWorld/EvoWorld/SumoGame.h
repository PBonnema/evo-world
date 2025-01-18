#pragma once
#include <chrono>
#include <random>
#include <unordered_map>

#include "Arena.h"

class SumoGame
{
public:
    explicit SumoGame(Arena arena, size_t participant_count, std::random_device::result_type seed);

    [[nodiscard]] const Arena& get_arena() const;
    [[nodiscard]] const std::unordered_map<std::shared_ptr<Creature>, std::shared_ptr<Glider>>& get_participants() const;
    void update(const std::chrono::nanoseconds& time_step, std::random_device::result_type seed);

private:
    const double max_force_amplitude_{1.0};
    const double friction_amplitude_{0.1};
    const double participant_radius_{20.0};
    const double participant_mass_{1.0};

    const Arena arena_;
    std::unordered_map<std::shared_ptr<Creature>, std::shared_ptr<Glider>> participants_;
    const size_t participant_count_;
};
