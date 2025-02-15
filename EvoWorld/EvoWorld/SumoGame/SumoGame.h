#pragma once
#include "Arena.h"
#include "../fwd_decl.h"

#include <chrono>
#include <random>

class SumoGame
{
public:
    explicit SumoGame(const std::mt19937& random_generator, Arena arena, size_t participant_count, double max_acceleration,
                      double coefficient_of_friction, double participant_radius, double participant_mass,
                      const std::vector<std::shared_ptr<Glider>>& initial_participants);

    [[nodiscard]] const Arena& get_arena() const;
    [[nodiscard]] const std::vector<std::shared_ptr<Glider>>& get_participants() const;
    [[nodiscard]] double get_max_acceleration() const;
    [[nodiscard]] double get_coefficient_of_friction() const;
    [[nodiscard]] double get_participant_radius() const;
    [[nodiscard]] double get_participant_mass() const;
    [[nodiscard]] size_t get_max_participant_count() const;
    void update(const std::chrono::high_resolution_clock::time_point& now, const std::chrono::duration<double>& time_step) const;

private:
    const double max_acceleration_;
    const double coefficient_of_friction_;
    const double participant_radius_;
    const double participant_mass_;
    const size_t max_participant_count_;

    Arena arena_;
    std::vector<std::shared_ptr<Glider>> participants_;
    mutable std::mt19937 random_generator_;

    void add_new_participant();
    void remove_outside_participants(std::vector<std::shared_ptr<Glider>>& participants) const;
    void reset_outside_participants(const std::vector<std::shared_ptr<Glider>>& participants) const;
};
