#include "SumoGame.h"
#include "Glider.h"
#include "Vector2.h"

#include <chrono>
#include <numbers>
#include <random>
#include <ranges>
#include <unordered_map>

SumoGame::SumoGame(Arena arena, const size_t participant_count, const std::mt19937& random_generator) :
    arena_{std::move(arena)},
    max_participant_count_{participant_count},
    random_generator_{random_generator}
{
    // while (participants_.size() < max_participant_count_)
    // {
    //     add_new_participant();
    // }


    // This length calculation ensures the distribution is uniform in the arena
    participants_.emplace_back(std::make_unique<Glider>(Vector2{0.0, 0.0} + arena_.get_center() + Vector2<double>::from_polar(0.0, -400.0), participant_mass_, participant_radius_));
    participants_[0]->apply_impulse({100.0, 0.0}, std::chrono::duration<double>{1.0});
    participants_.emplace_back(std::make_unique<Glider>(Vector2{0.0, 0.0} + arena_.get_center() + Vector2<double>::from_polar(0.0, 400.0), participant_mass_, participant_radius_));
    participants_[1]->apply_impulse({-100.0, 0.0}, std::chrono::duration<double>{1.0});
}

const Arena& SumoGame::get_arena() const
{
    return arena_;
}

const std::vector<std::shared_ptr<Glider>>& SumoGame::get_participants() const
{
    return participants_;
}

Vector2<double> SumoGame::calculate_friction(const Glider& glider, const std::chrono::duration<double>& time_step) const
{
    const auto speed = glider.get_velocity().get_length();
    if (speed == 0.0)
    {
        return {0.0, 0.0};
    }

    // The gravitational constant is implicitly set to 1
    auto friction_magnitude = glider.get_mass() * coefficient_of_friction_;

    // Scale the friction such that the impulse does not exceed the remaining momentum of the glider within this time step
    // This prevents the glider from moving backwards. It can come to a full stop.
    const auto friction_impulse = friction_magnitude * time_step.count();
    const auto remaining_momentum = speed * glider.get_mass();
    if (friction_impulse > remaining_momentum)
    {
        friction_magnitude *= remaining_momentum / friction_impulse;
    }

    return glider.get_velocity() / (speed / -friction_magnitude);
}

void SumoGame::remove_outside_participants(std::vector<std::shared_ptr<Glider>>& participants) const
{
    for (auto it = participants.begin(); it != participants.end();)
    {
        if (!arena_.contains((*it)->get_position()))
        {
            it = participants.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void SumoGame::update(const std::chrono::duration<double>& time_step)
{
    // Ask each creature for their next move (= preferred force)
    // sum up forces for each creature and add friction based on their velocity
    // do physics simulation for each creature, according to the time_step
    // including collision detection and make creatures bounce
    // update positions of creatures using the position of gliders
    // if a creature is outside the arena, remove it

    // TODO detach game loop from rendering loop
    // TODO implement collision detection and make creatures bounce

    std::unordered_map<std::shared_ptr<Glider>, Vector2<double>> moves;
    for (const auto& glider : participants_)
    {
        const Vector2<double> move_force = glider->next_sumo_move(get_participants(), max_force_magnitude_, coefficient_of_friction_);

        // Assert the move force magnitude is no more than the maximum force magnitude. Otherwise, next_sumo_move is bugged. No need to check at run time otherwise.
        assert(move_force.get_length_squared() <= max_force_magnitude_ * max_force_magnitude_ + 0.0001); // Allow for a bit of numerical error

        moves[glider] = move_force;
    }

    for (const auto& [glider, move_force] : moves)
    {
        const auto friction = calculate_friction(*glider, time_step);

        // Sum up all forces and apply them
        const auto total_force = move_force + friction;
        glider->apply_impulse(total_force, time_step);
    }

    // Collision detection
    std::unordered_map<std::shared_ptr<Glider>, std::shared_ptr<Glider>> collisions;
    for (const auto& glider : participants_)
    {
        for (const auto& other_glider : participants_)
        {
            // TODO don't register all collisions twice
            if (glider == other_glider)
            {
                continue;
            }

            const auto distance_squared = glider->get_position().distance_squared(other_glider->get_position());
            const auto radius_sum = glider->get_radius() + other_glider->get_radius();
            if (distance_squared < radius_sum * radius_sum)
            {
                collisions[glider] = other_glider;
            }
        }
    }

    // Bounce the gliders by setting their velocity to the opposite direction
    for (const auto& [glider, other_glider] : collisions)
    {
        // TODO Move the gliders apart along the direction of their velocity so they don't overlap. The offset for both should be proportional to their velocity.

        // Bounce
        const auto normal = (other_glider->get_position() - glider->get_position()).get_normalized();
        const auto relative_velocity = other_glider->get_velocity() - glider->get_velocity();
        const auto velocity_along_normal = relative_velocity.dot(normal);

        if (velocity_along_normal > 0.0)
        {
            continue; // No collision if moving apart
        }

        constexpr auto e = 1.0; // Perfectly elastic collision
        const auto impulse_magnitude = -(1.0 + e) * velocity_along_normal / (1.0 / glider->get_mass() + 1.0 / other_glider->get_mass());

        const auto impulse = normal * impulse_magnitude;
        glider->add_velocity(-impulse / glider->get_mass());
        other_glider->add_velocity(impulse / other_glider->get_mass());
    }

    // Remove participants that are outside the arena
    remove_outside_participants(participants_);

    // Add new participants if there are less than the desired number of participants
    // TODO deal with participants spawning inside each other
    // while (participants_.size() < max_participant_count_)
    // {
    //     add_new_participant();
    // }
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
