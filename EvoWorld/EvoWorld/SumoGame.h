#pragma once
#include "Arena.h"

#include <chrono>
#include <random>

class SumoGame
{
public:
    explicit SumoGame(Arena arena, size_t participant_count, const std::mt19937& random_generator);

    [[nodiscard]] const Arena& get_arena() const;
    [[nodiscard]] std::ranges::view auto get_participants() const
    {
        return participants_ | std::views::transform([](auto&& p) { return p.get(); });
    }
    void update(const std::chrono::duration<double>& time_step);

private:
    const double max_force_magnitude_{500.0};
    const double coefficient_of_friction_{400.0};
    const double participant_radius_{50.0};
    const double participant_mass_{1.0};

    Arena arena_;
    std::vector<std::shared_ptr<Glider>> participants_;
    const size_t max_participant_count_;
    std::mt19937 random_generator_;

    void add_new_participant();
};
