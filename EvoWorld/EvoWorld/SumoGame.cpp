#include "SumoGame.h"
#include "Glider.h"
#include "Vector2.h"

#include <chrono>
#include <numbers>
#include <random>
#include <ranges>

SumoGame::SumoGame(Arena arena, const size_t participant_count, const std::mt19937& random_generator) :
    arena_{std::move(arena)},
    max_participant_count_{participant_count},
    random_generator_{random_generator}
{
    while (participants_.size() < max_participant_count_)
    {
        add_new_participant();
    }
}

const Arena& SumoGame::get_arena() const
{
    return arena_;
}

void SumoGame::update(const std::chrono::duration<double>& time_step)
{
    // Ask each creature for their next move (= preferred force)
    // sum up forces for each creature and add friction based on their velocity
    // do physics simulation for each creature, according to the time_step
    // including collision detection and make creatures bounce
    // update positions of creatures using the position of gliders
    // if a creature is outside the arena, remove it

    for (const auto& glider : participants_)
    {
        const Vector2<double> move_force = glider->next_sumo_move(get_participants(), max_force_magnitude_, coefficient_of_friction_);

        // Assert the force magnitude is no more than the maximum force magnitude. Otherwise, next_sumo_move is bugged.
        assert(move_force.get_length() <= max_force_magnitude_ + 0.0001); // Allow for a bit of numerical error

        // Apply friction
        // The gravitational constant is implicitly set to 1
        auto friction_magnitude = glider->get_mass() * coefficient_of_friction_;

        // Scale the friction such that the impulse does not exceed the remaining momentum of the glider within this time step
        const auto friction_impulse = friction_magnitude * time_step.count();
        const auto speed = glider->get_velocity().get_length();
        const auto remaining_momentum = speed * glider->get_mass();
        if (friction_impulse > remaining_momentum)
        {
            friction_magnitude *= remaining_momentum / friction_impulse;
        }
        const auto friction = glider->get_velocity() / (speed * -friction_magnitude);

        // Sum up all forces and apply them
        const auto total_force = move_force + friction;
        glider->apply_impulse(total_force, time_step);
    }

    // TODO call next_sumo_move on a regular interval instead of every frame and remember the last move
    // TODO collect all moves before applying them to avoid bias
    // TODO implement collision detection and make creatures bounce

    // Remove participants that are outside the arena
    for (auto it = participants_.begin(); it != participants_.end();)
    {
        const Glider& glider = **it;
        const auto participant_center = glider.get_position() + Vector2{glider.get_radius(), glider.get_radius()};
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
    while (participants_.size() < max_participant_count_)
    {
        add_new_participant();
    }
}

void SumoGame::add_new_participant()
{
    // Create creature at a uniform, random position within the circular arena
    std::uniform_real_distribution polar_angle_distribution{0.0, std::numbers::pi * 2};
    std::uniform_real_distribution polar_length_distribution{0.0, 1.0};

    const auto angle = polar_angle_distribution(random_generator_);
    // This length calculation ensures the distribution is uniform in the arena
    const auto distance_from_center = arena_.get_radius() * std::sqrt(polar_length_distribution(random_generator_));
    const auto position = arena_.get_center() + Vector2<double>::from_polar(angle, distance_from_center);

    participants_.emplace_back(std::make_unique<Glider>(position, participant_mass_, participant_radius_));
}
