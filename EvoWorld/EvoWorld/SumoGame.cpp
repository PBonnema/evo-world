#include "SumoGame.h"
#include "Creature.h"
#include "Glider.h"
#include "Vector2.h"

#include <chrono>
#include <iostream>
#include <numbers>
#include <random>
#include <ranges>

SumoGame::SumoGame(Arena arena, const size_t participant_count, const std::mt19937& random_generator) :
    arena_{std::move(arena)},
    participant_count_{participant_count},
    random_generator_{random_generator}
{
    while (participants_.size() < participant_count_)
    {
        add_new_participant();
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

void SumoGame::update(const std::chrono::nanoseconds& time_step)
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
        const Vector2<double> move_force = glider->next_sumo_move(
            participants_ | std::views::values,
            max_force_amplitude_, coefficient_of_friction_);

        // Assert the force amplitude is no more than the maximum force amplitude. Otherwise, next_sumo_move is bugged.
        assert(move_force.get_length() <= max_force_amplitude_ + 0.0001); // Allow for a bit of numerical error

        // Apply friction
        // The gravitational constant is implicitly set to 1
        const double friction_amplitude = glider->get_mass() * coefficient_of_friction_;
        const Vector2<double> friction = glider->get_velocity().get_normalized() * -friction_amplitude;

        // Sum up all forces and apply them
        const Vector2<double> total_force = move_force + friction;
        glider->apply_impulse(total_force, time_step);
        creature->set_position(glider->get_position());
    }

    // TODO call next_sumo_move on a regular interval instead of every frame and remember the last move
    // TODO collect all moves before applying them to avoid bias

    // Remove participants that are outside the arena
    for (auto it = participants_.begin(); it != participants_.end();)
    {
        auto [_, glider] = *it;
        const Vector2<double> participant_center = glider->get_position() + Vector2{glider->get_radius(), glider->get_radius()};
        if (!arena_.contains(participant_center))
        {
            it = participants_.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // Add new participants if there are less than the desired number of participants
    while (participants_.size() < participant_count_)
    {
        add_new_participant();
    }
}

void SumoGame::add_new_participant()
{
    // Create creature at a uniform, random position within the circular arena
    std::uniform_real_distribution polar_angle_distribution{0.0, std::numbers::pi * 2};
    std::uniform_real_distribution polar_length_distribution{0.0, 1.0};

    const double angle = polar_angle_distribution(random_generator_);
    // This length calculation ensures the distribution is uniform in the arena
    const double distance_from_center = arena_.get_radius() * std::sqrt(polar_length_distribution(random_generator_));
    const Vector2 position = arena_.get_center() + Creature::position::from_polar(angle, distance_from_center);

    participants_.emplace(std::make_shared<Creature>(position, participant_radius_),
                          std::make_shared<Glider>(position, participant_mass_, participant_radius_));
}
