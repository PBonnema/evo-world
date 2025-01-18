#include "SumoGame.h"
#include "Creature.h"
#include "Glider.h"
#include "Vector2.h"

#include <chrono>
#include <iostream>
#include <numbers>
#include <random>
#include <ranges>

SumoGame::SumoGame(Arena arena, const size_t participant_count, const std::random_device::result_type seed) :
    arena_{std::move(arena)},
    participant_count_{participant_count}
{
    std::mt19937 generator{seed};
    participants_.reserve(participant_count); // The number of participants will not change so we can do this safely

    const Vector2 arena_center{arena_.get_radius(), arena_.get_radius()};
    std::uniform_real_distribution polar_angle_distribution{0.0, std::numbers::pi * 2};
    std::uniform_real_distribution polar_length_distribution{0.0, 1.0};
    for (size_t i = 0; i < participant_count; i++)
    {
        // Create creature at a uniform, random position within the circular arena
        const double angle = polar_angle_distribution(generator);
        const double length = arena_.get_radius() * std::sqrt(polar_length_distribution(generator));
        const Vector2 position = arena_center + Creature::position::from_polar(angle, length);
        participants_.emplace(std::make_shared<Creature>(position),
                              std::make_shared<Glider>(position, participant_mass_, participant_radius_));
    }
}

const Arena& SumoGame::get_arena() const
{
    return arena_;
}

const std::unordered_map<std::shared_ptr<Creature>, std::shared_ptr<Glider>>& SumoGame::get_participants() const
{
    return participants_;
}

void SumoGame::update(const std::chrono::nanoseconds& time_step, const std::random_device::result_type seed)
{
    // Ask each creature for their next move (= preferred force)
    // Clamp their chosen force amplitude to a maximum force
    // sum up forces for each creature and add friction based on their velocity
    // do physics simulation for each creature, according to the time_step
    // including collision detection and make creatures bounce
    // update positions of creatures using the position of gliders
    // if a creature is outside the arena, remove it

    for (const auto& [creature, glider] : participants_)
    {
        const Vector2<double> force = glider->next_sumo_move(
            participants_ | std::views::values,
            max_force_amplitude_, friction_amplitude_);

        // Clamp the force to the maximum force amplitude and apply it
        const Vector2<double> clamped_force = force.get_clamped_by_length(0.0, max_force_amplitude_);

        // Apply friction
        const Vector2<double> friction = glider->get_velocity().get_normalized() * -friction_amplitude_;

        // Sum up all forces and apply them
        const Vector2<double> total_force = clamped_force + friction;
        glider->apply_impulse(total_force, time_step);

        glider->update_physics(time_step);
        creature->set_position(glider->get_position());
    }

    // TODO collect all moves before applying them to avoid bias

    // Remove participants that are outside the arena
    for (auto it = participants_.begin(); it != participants_.end();)
    {
        if (!arena_.contains(it->second->get_position()))
        {
            it = participants_.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // Add new participants if there are less than the desired number of participants
    std::mt19937 generator{seed};
    std::uniform_real_distribution polar_angle_distribution{0.0, std::numbers::pi * 2};
    std::uniform_real_distribution polar_length_distribution{0.0, 1.0};
    while (participants_.size() < participant_count_)
    {
        const Vector2 position = arena_.get_midpoint() + Creature::position::from_polar(
            polar_angle_distribution(generator), arena_.get_radius() * std::sqrt(polar_length_distribution(generator)));
        participants_.emplace(std::make_shared<Creature>(position),
                              std::make_shared<Glider>(position, participant_mass_, participant_radius_));
    }
}
