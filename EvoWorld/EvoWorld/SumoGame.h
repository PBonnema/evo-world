#pragma once
#include <chrono>
#include <random>
#include <unordered_map>

#include "Arena.h"

class SumoGame
{
public:
    explicit SumoGame(Arena arena, size_t participant_count, const std::mt19937& random_generator);

    [[nodiscard]] const Arena& get_arena() const;
    [[nodiscard]] const std::unordered_map<std::shared_ptr<Creature>, std::shared_ptr<Glider>>& get_participants() const;
    void update(const std::chrono::nanoseconds& time_step);

private:
    const double max_force_amplitude_{1000000.0};
    const double coefficient_of_friction_{300000.0};
    const double participant_radius_{50.0};
    const double participant_mass_{1.0};

    const Arena arena_;
    std::unordered_map<std::shared_ptr<Creature>, std::shared_ptr<Glider>> participants_;
    const size_t participant_count_;
    std::mt19937 random_generator_;

    void add_new_participant();
};
