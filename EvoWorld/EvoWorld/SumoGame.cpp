#include "SumoGame.h"

#include <chrono>
#include <iostream>
#include <numbers>
#include <random>

#include "Creature.h"
#include "Vector2.h"

SumoGame::SumoGame(Arena arena, const size_t participant_count, const std::random_device::result_type seed) :
    arena_{std::move(arena)}
{
    std::mt19937 generator{seed};
    participants_.reserve(participant_count); // The number of participants will not change so we can do this safely

    const Vector2 arena_center{arena_.get_radius(), arena_.get_radius()};
    std::uniform_real_distribution polar_angle_distribution{0.0, std::numbers::pi * 2};
    std::uniform_real_distribution polar_length_distribution{0.0, 1.0};
    for (size_t i = 0; i < participant_count; i++)
    {
        // Create creature at a uniform, random position within the circular arena
        participants_.emplace_back(std::make_shared<Creature>(arena_center + Creature::position::from_polar(
            polar_angle_distribution(generator),
            arena_.get_radius() * std::sqrt(polar_length_distribution(generator)))));
    }
}

const Arena& SumoGame::get_arena() const
{
    return arena_;
}

const std::vector<std::shared_ptr<Creature>>& SumoGame::get_participants() const
{
    return participants_;
}

void SumoGame::update(const std::chrono::duration<double, std::milli>& time_step) const
{
    const Vector2 arena_center{arena_.get_radius(), arena_.get_radius()};
    double speed = 0.01;
    for (const std::shared_ptr<Creature>& creature : participants_)
    {
        speed += 0.01;
        // Move creature towards the center of the arena with a constant velocity
        const Vector2 displacement = (arena_center - creature->get_position()).get_normalized() * speed * time_step.count();
        creature->move(displacement);
    }
}
