#pragma once
#include "Arena.h"

#include <chrono>
#include <random>
#include <unordered_map>

class SumoGame
{
public:
    explicit SumoGame(Arena arena, size_t participant_count, const std::mt19937& random_generator);

    [[nodiscard]] const Arena& get_arena() const;
    [[nodiscard]] const std::vector<std::shared_ptr<Glider>>& get_participants() const;
    void update(const std::chrono::duration<double>& time_step);

private:
    const double max_force_magnitude_{500.0};
    const double coefficient_of_friction_{100.0};
    const double participant_radius_{50.0};
    const double participant_mass_{1.0};

    Arena arena_;
    std::vector<std::shared_ptr<Glider>> participants_;
    const size_t max_participant_count_;
    std::mt19937 random_generator_;

    void add_new_participant();
    Vector2<double> calculate_friction(const Glider& glider, const std::chrono::duration<double>& time_step) const;
    void remove_outside_participants(std::vector<std::shared_ptr<Glider>>& participants) const;
    static std::unordered_map<std::shared_ptr<Glider>, std::shared_ptr<Glider>> detect_collisions(const std::vector<std::shared_ptr<Glider>>& participants);
    static void resolve_collision(Glider& glider, Glider& other_glider);
};
